//
// Created by Khyber on 6/24/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "src/main/runtime/coverage/branch/execute/BranchExecutionRuntime.h"
#include "src/main/pass/coverage/branch/SwitchCaseSuccessors.h"
#include "src/share/stde/forEachRemovable.h"

namespace llvm::pass::coverage::branch {
    
    class BranchExecutionPass : public NamedRegisteredPass<BranchExecutionPass> {
    
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
            
            const llvm::Api api;
            
            const NextBranch nextBranch;
            const FunctionCallee onEdge;
            Type& funcPtrType;
            
            Api(std::string_view name, Module& module)
                    : api(name, module),
                      nextBranch(api),
                      onEdge(api.func<void(u64, u64)>("onEdge")),
                      funcPtrType(api.types.get<Func*>()) {}
            
            void addFunctionTable(Module& module, ArrayRef<Constant*> functionPointers) const {
                using llvm::Api;
                api.global<u64>("numFunctions", Api::GlobalArgs {
                        .module = &module,
                        .isConstant = true,
                        .initializer = Constants(module.getContext()).getInt(functionPointers.size()),
                });
                auto& arrayType = api.types.array(funcPtrType, functionPointers.size());
                api.global(
                        "functions",
                        arrayType,
                        Api::GlobalArgs {
                                .module = &module,
                                .isConstant = true,
                                .initializer = *ConstantArray::get(&arrayType, functionPointers),
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
                inst.removeFromParent();
                if (inst.isConditional()) {
                    auto& condition = irbe.call(api.nextBranch.single, {});
                    inst.setCondition(&condition);
                }
                irbe.insert(inst);
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
                auto& castedFunctionPtr = irbe.bitCast(functionPtr, *inst.getFunctionType()->getPointerTo());
                inst.setCalledOperand(&castedFunctionPtr);
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
                auto& funcType = *inst.getFunctionType();
                for (auto i = 0u; i < funcType.getNumParams(); i++) {
                    inst.setArgOperand(i, UndefValue::get(funcType.getParamType(i)));
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
                        return transformCall(casted<CallBase>());
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
            
            class BlockTransform {
            
            private:
                
                BasicBlock& _transformed;
                std::unique_ptr<BasicBlock> _original;
                
                static BasicBlock& createBasedOff(BasicBlock& original) {
                    return *BasicBlock::Create(original.getContext(), original.getName());
                }
            
            public:
                
                constexpr BasicBlock& original() const noexcept {
                    return *_original;
                }
                
                constexpr BasicBlock& transformed() const noexcept {
                    return _transformed;
                }
            
            private:
                
                void swapInstructions() {
                    original().getInstList().splice(original().begin(), transformed().getInstList());
                }
            
            public:
                
                explicit BlockTransform(BasicBlock& original, IRBuilderExt& irbe)
                        : _transformed(original), _original(&createBasedOff(original)) {
                    swapInstructions();
                    irbe.setInsertPoint(transformed());
                }
                
                ~BlockTransform() {
                    while (!original().empty()) {
                        original().getInstList().pop_back();
                    }
                }
                
            };
            
            BlockTransform block;
            const Api& api;
            IRBuilderExt& irbe;
        
        public:
            
            BlockPass(BasicBlock& originalBlock, const Api& api, IRBuilderExt& irbe) noexcept
                    : block(originalBlock, irbe), api(api), irbe(irbe) {}
            
            void transform() {
                stde::forEachRemovable(llvm::reverse(block.original()), [this](Instruction& inst) {
                    irbe.setInsertPoint(block.transformed(), true);
                    InstructionPass(api, inst, irbe)();
                });
            }
            
            void operator()() {
                transform();
            }
            
        };
        
        class FunctionPass {
        
        private:
            
            Function& function;
            const Api& api;
            IRBuilderExt& irbe;
        
        public:
            
            constexpr FunctionPass(Function& function, const Api& api,
                                   IRBuilderExt& irbe) noexcept
                    : function(function), api(api), irbe(irbe) {}
            
            void transform() {
                for (auto& block : llvm::reverse(function)) {
                    BlockPass(block, api, irbe)();
                }
            }
            
            void operator()() {
                transform();
            }
            
        };
        
        class ModulePass {
        
        private:
            
            Module& module;
        
        public:
            
            explicit constexpr ModulePass(Module& module) : module(module) {}
        
        private:
            
            static bool shouldRemove(const Function& func) noexcept {
                return func.empty() || func.isDeclaration() || runtimeFunctionFilter()(func.getName());
            }
        
        private:
            
            void doTransform() const {
                const Api api("BranchExecution", module);
                IRBuilderExt irbe(module);
                SmallVector<Constant*, 0> functionPointers;
                for (auto& function : module) {
                    if (!shouldRemove(function)) {
                        FunctionPass(function, api, irbe)();
                        functionPointers.push_back(ConstantExpr::getBitCast(&function, &api.funcPtrType));
                    }
                }
                api.addFunctionTable(module, functionPointers);
            }
        
        public:
            
            bool transform() const {
                doTransform();
                return true;
            }
            
            bool operator()() const {
                return transform();
            }
            
        };
    
    public:
        
        static constexpr auto name = "Branch Execution Pass";
        
        bool runOnModule(Module& module) override {
            return ModulePass(module)();
        }
        
    };
    
    bool registered = BranchExecutionPass::register_();
    
}
