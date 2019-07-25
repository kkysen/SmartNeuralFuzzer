//
// Created by Khyber on 6/24/2019.
//

#include "src/main/pass/coverage/includes.h"

#include "src/main/runtime/coverage/branch/execute/BranchExecutionRuntime.h"
#include "src/main/pass/coverage/branch/SwitchCaseSuccessors.h"

namespace llvm::pass::coverage::branch {
    
    class BranchExecutionPass : public NamedRegisteredPass<BranchExecutionPass> {
    
    private:
        
        struct NextBranch {
            const FunctionCallee single;
            const FunctionCallee multi;
            const FunctionCallee infinite;
        };
        
        struct Api {
            const NextBranch nextBranch;
            const FunctionCallee onEdge;
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
                const auto name = irbe.function().getName();
                ;
                const bool print = (StringSet {
                    "d_clone_suffix",
                    "ada_demangle",
                    "cplus_demangle_type",
                    "d_array_type",
                    "d_java_resource",
                    "d_pack_length",
                    "d_args_length",
//                    "only_whitespace",
                    "dlang_parse_qualified",
                    "dlang_function_args",
                    "dlang_template_args",
                }).count(name) > 0;
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
            
            class BlockTransform {
            
            private:
                
                BasicBlock& transformed;
                std::unique_ptr<BasicBlock> _original;
                
                static BasicBlock& createBasedOff(BasicBlock& original) {
                    return *BasicBlock::Create(original.getContext(), original.getName());
                }
            
            public:
                
                constexpr BasicBlock& original() const noexcept {
                    return *_original;
                }
                
                explicit BlockTransform(BasicBlock& realOriginal, IRBuilderExt& irbe)
                        : transformed(realOriginal), _original(&createBasedOff(realOriginal)) {
                    original().getInstList().splice(original().begin(), transformed.getInstList());
                    irbe.setInsertPoint(transformed);
                }
                
            };
            
            const Api& api;
            BlockTransform block;
            IRBuilderExt& irbe;
        
        public:
            
            BlockPass(const Api& api, BasicBlock& originalBlock, IRBuilderExt& irbe) noexcept
                    : api(api), block(originalBlock, irbe), irbe(irbe) {}
            
            bool transform() {
                for (auto it = block.original().begin(); it != block.original().end();) {
                    // it++ is necessary b/c inst might be removed,
                    // so we need to advance the iterator first before using the current value
                    auto& inst = *(it++);
                    InstructionPass(api, inst, irbe)();
                }
                return true;
            }
            
            bool operator()() {
                return transform();
            }
            
        };
    
    public:
        
        static constexpr auto name = "Branch Execution Pass";
        
        bool runOnModule(Module& module) override {
//            errs() << *module.getFunction("ada_demangle");
            
            using llvm::Api;
            const Api api("BranchExecution", module);
            using runtime::coverage::branch::execute::Func;
            const BranchExecutionPass::Api ownApi = {
                    .nextBranch = {
                            .single = api.func<bool()>("nextSingleBranch"),
                            .multi = api.func<u64(u64)>("nextMultiBranch"),
                            .infinite = api.func<Func*()>("nextInfiniteBranch"),
                    },
                    .onEdge = api.func<void(u64, u64)>("onEdge"),
            };
            SmallVector<Constant*, 0> functions;
            IRBuilderExt irbe(module);
//            u64 blockIndex = 0;
            const bool modified = filteredFunctions(module)
                    .forEach([&](BasicBlock& block) -> bool {
//                        errs() << &block << '\n';
//                        errs() << '\t' << "BranchExecution: block: " << blockIndex++;
//                        errs() << '\n';
//                        errs() << block;
                        const bool ret = BlockPass(ownApi, block, irbe)();
//                        errs() << block;
                        return ret;
                    }, [&](Function& function) {
//                        errs() << "BranchExecution: function: " << function.getName() << '\n';
                        functions.emplace_back(&function);
                        // make all functions 0 arg and void, i.e. void()
//                        errs() << function << '\n';
//                        errs() << function.getType() << '\n';
//                        errs() << function.getFunctionType() << '\n';
                    });
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
            
//            auto& f = *module.getFunction("ada_demangle");
//            errs() << f.getName() << '\n';
//            for (auto& b : f) {
//                for (auto& i : b) {
//                    errs() << &i << '\n';
//                    errs() << i.getOpcodeName() << '\n';
//                    switch (i.getOpcode()) {
//                        case Instruction::Call: {
//                            auto& call = cast<CallInst>(i);
//                            errs() << call.getCalledFunction()->getName() << '\n';
//                            errs() << *call.getFunctionType() << '\n';
//                        }
//                    }
////                    errs() << i << '\n';
//                    errs() << '\n';
//                }
//            }
            errs() << "\n\n\n";
            return modified;
        }
        
    };
    
    bool registered = BranchExecutionPass::register_();
    
}
