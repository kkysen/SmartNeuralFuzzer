//
// Created by Khyber on 6/24/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "src/main/runtime/coverage/branch/execute/BranchExecutionRuntime.h"
#include "src/main/pass/coverage/branch/SwitchCaseSuccessors.h"

namespace llvm::pass::coverage::branch {
    
    class BranchExecutionPass : public ModulePass {
    
    private:
        
        using Func = runtime::coverage::branch::execute::Func;
        
        struct NextBranch {
            
            const FunctionCallee single;
            const FunctionCallee multi;
            const FunctionCallee infinite;
            
            explicit NextBranch(const llvm::Api& api)
                    : single(api.func<bool()>("nextSingleBranch")),
                      multi(api.func<u64(u64)>("nextMultiBranch")),
                      infinite(api.func<Func*()>("nextInfiniteBranch")) {}
            
        };
        
        struct Api {
            
            const llvm::Api& api;
            
            const NextBranch nextBranch;
            const FunctionCallee onEdge;
            FunctionType& funcType;
            
            explicit Api(const llvm::Api& api)
                    : api(api),
                      nextBranch(api),
                      onEdge(api.func<void(u64, u64)>("onEdge")),
                      funcType(api.types.func<Func>()) {}
            
            Api(std::string_view name, Module& module) : Api(llvm::Api(name, module)) {}
            
            void addFunctionTable(Module& module, ArrayRef<Constant*> functions) const {
                using llvm::Api;
                api.global<u64>("numFunctions", Api::GlobalArgs {
                        .module = &module,
                        .isConstant = true,
                        .initializer = Constants(module.getContext()).getInt(functions.size()),
                });
                auto& arrayType = api.types.array<Func>(functions.size());
                api.global(
                        "functions",
                        arrayType,
                        Api::GlobalArgs {
                                .module = &module,
                                .isConstant = true,
                                .initializer = *ConstantArray::get(&arrayType, functions),
                        });
            }
            
        };
        
        class InstructionPass {
        
        private:
            
            const Api& api;
            Instruction& instruction;
            IRBuilderExt& irbe;
        
        public:
            
            constexpr InstructionPass(const Api& api, Instruction& instruction, IRBuilderExt& irbe) noexcept
                    : api(api), instruction(instruction), irbe(irbe) {}
        
        private:
            
            void transformBranch(BranchInst& inst) const {
                const bool print = irbe.function().getName() == "ada_demangle" || true;
                if (print) {
                    errs() << inst << '\n';
                }
                inst.removeFromParent();
                if (inst.isConditional()) {
                    auto& condition = irbe.call(api.nextBranch.single, {});
                    if (print) {
                        errs() << condition << '\n';
                    }
                    inst.setCondition(&condition);
                }
                irbe.insert(inst);
                if (print) {
                    errs() << inst << '\n';
                }
            }
            
            void transformSwitch(SwitchInst& inst) const {
                SwitchCaseSuccessors successors;
                successors.findUniqueBranches(inst);
                const auto numBranches = successors.numBranches();
                // TODO preserve branch weights if possible
                auto& switchValue = irbe.call(api.nextBranch.multi, {&irbe.constants().getInt(numBranches)});
                auto& switchInst = irbe.switchCase(switchValue, *inst.getDefaultDest(), numBranches);
                u64 i = 0;
                for (auto* successor : successors.get()) {
                    switchInst.addCase(&irbe.constants().getInt(i++), successor);
                }
            }
            
            void transformSelectCall(SelectInst& select) const {
                if (!select.getCondition()) {
                    return;
                }
                select.removeFromParent();
                auto& condition = irbe.call(api.nextBranch.single, {});
                select.setCondition(&condition);
                irbe.insert(select);
            }
            
            void transformTrueIndirectCall(CallBase& inst) const {
                auto& functionPtr = irbe.call(api.nextBranch.infinite, {});
                inst.setCalledOperand(&functionPtr);
            }
            
            void transformIndirectCall(CallBase& inst) const {
                auto& functionPtr = *inst.getCalledOperand();
                if (isa<SelectInst>(functionPtr)) {
                    transformSelectCall(cast<SelectInst>(functionPtr));
                } else {
                    transformTrueIndirectCall(inst);
                }
            }
            
            void transformCall(CallBase& inst) const {
                if (!inst.getCalledOperand()) {
                    return;
                }
                if (inst.isIndirectCall()) {
                    transformIndirectCall(inst);
                } else {
                    auto& func = *inst.getCalledFunction();
                    if (func.isDeclaration() || runtimeFunctionFilter()(func.getName())) {
                        return;
                    }
                }
                inst.removeFromParent();
                for (auto& arg : inst.args()) {
                    arg.set(UndefValue::get(arg.get()->getType()));
                }
                irbe.insert(inst);
            }
            
            void transformIndirectBranch(IndirectBrInst&) const {
                llvm_unreachable("indirectbr not supported yet");
                // TODO
            }
            
            void transformReturnAndResume() const {
                if (instruction.getNumOperands() > 0) {
                    auto& op = instruction.op_begin()[0];
                    op.set(UndefValue::get(op.get()->getType()));
                }
            }
            
            template <class InstType>
            InstType& casted() const {
                return cast<InstType>(instruction);
            }
            
            void transformTerminator() const {
                switch (instruction.getOpcode()) {
                    case Instruction::Br:
                        return transformBranch(casted<BranchInst>());
                    case Instruction::Switch:
                        return transformSwitch(casted<SwitchInst>());
                    case Instruction::Invoke:
                    case Instruction::CallBr:
                        return transformCall(casted<CallBase>());
                    case Instruction::IndirectBr:
                        return transformIndirectBranch(casted<IndirectBrInst>());
                    case Instruction::Ret:
                    case Instruction::Resume:
                        transformReturnAndResume();
                        // fallthrough
                    default:
                        instruction.removeFromParent();
                        irbe.insert(instruction);
                }
            }
            
            void transformNonTerminator() const {
                switch (instruction.getOpcode()) {
                    case Instruction::Call:
                        return transformCall(cast<CallBase>(instruction));
                }
            }
        
        public:
            
            void transform() const {
                if (__builtin_expect(instruction.isTerminator(), false)) {
                    transformTerminator();
                } else {
                    transformNonTerminator();
                }
            }
            
            void operator()() const {
                transform();
            }
            
        };
        
        class BlockPass {
        
        private:
            
            BasicBlock& original;
            const Api& api;
            IRBuilderExt& irbe;
        
        public:
            
            BlockPass(BasicBlock& original, BasicBlock& transformed, const Api& api, IRBuilderExt& irbe) noexcept
                    : original(original), api(api), irbe(irbe) {
                irbe.setInsertPoint(transformed);
            }
            
            void transform() {
                for (auto it = original.begin(); it != original.end();) {
                    // it++ is necessary b/c inst might be removed,
                    // so we need to advance the iterator first before using the current value
                    auto& inst = *(it++);
                    InstructionPass(api, inst, irbe)();
                }
            }
            
            void operator()() {
                transform();
            }
            
        };
        
        class FunctionPass {
        
        private:
            
            Function& original;
            Function& transformed;
            const Api& api;
            IRBuilderExt& irbe;
        
        public:
            
            constexpr FunctionPass(Function& original, Function& transformed, const Api& api,
                                   IRBuilderExt& irbe) noexcept
                    : original(original), transformed(transformed), api(api), irbe(irbe) {}
            
            void transform() {
                for (auto& originalBlock : original) {
                    auto& transformedBlock = *BasicBlock::Create(
                            transformed.getContext(),
                            originalBlock.getName(),
                            &transformed
                    );
                    BlockPass(originalBlock, transformedBlock, api, irbe)();
                }
            }
            
            void operator()() {
                transform();
            }
            
        };
        
        class ModulePass {
        
        private:
            
            Module& module;
            const Api api;
            mutable IRBuilderExt irbe;
        
        public:
            
            explicit ModulePass(Module& module)
                    : module(module), api("BranchExecution", module), irbe(module) {}
        
        private:
            
            bool shouldRemove(const Function& func) const noexcept {
                return func.empty() || func.isDeclaration() || runtimeFunctionFilter()(func.getName());
            }
        
        public:
            
            bool transform() const {
                for (auto& function : module) {
                    if (shouldRemove(function)) {
                        function.eraseFromParent();
                    } else {
                        auto& original = function;
                        auto& transformed = *Function::Create(
                                &api.funcType,
                                GlobalValue::InternalLinkage,
                                module.getDataLayout().getProgramAddressSpace(),
                                function.getName()
                        );
                        FunctionPass(original, transformed, api, irbe)();
                        original.eraseFromParent();
                        module.getFunctionList().push_back(&transformed);
                    }
                }
                return true;
            }
            
            bool operator()() const {
                return transform();
            }
            
        };
    
    public:
        
        static char ID;
        
        BranchExecutionPass() : llvm::ModulePass(ID) {}
        
        StringRef getPassName() const override {
            return "Branch Execution Pass";
        }
        
        bool runOnModule(Module& module) override {
            return ModulePass(module)();
        }
        
    };
    
    char BranchExecutionPass::ID = 0;
    
    bool registered = registerStandardAlwaysLast<BranchExecutionPass>();
    
}
