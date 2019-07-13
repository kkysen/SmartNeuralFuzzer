//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include "src/share/llvm/Types.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"

#include <string_view>

namespace llvm {
    
    class Api {
    
    public:
        
        const std::string_view name;
    
    private:
        
        Module& module;
        
    public:
    
        const Types types;
        
        constexpr Api(std::string_view name, Module& module) noexcept
                : name(name), module(module), types(module.getContext()) {}
        
        std::string nameFor(std::string_view symbolName) const {
            using namespace std::literals;
            return (("__"s += name) += "_"sv) += symbolName;
        }
        
        template <typename... Args>
        FunctionCallee func(std::string_view funcName) const {
            return module.getOrInsertFunction(nameFor(funcName), types.function<Args...>());
        }
        
        struct GlobalArgs {
            Module* module;
            bool isConstant;
            GlobalValue::LinkageTypes linkage;
            Constant& initializer;
            GlobalVariable* insertBefore;
            GlobalValue::ThreadLocalMode threadLocalMode;
            u32 addressSpace;
            bool isExternallyInitialized;
        };
        
        Constant& global(std::string_view globalName, Type& type) const {
            return *module.getOrInsertGlobal(nameFor(globalName), &type);
        }
        
        Constant& global(std::string_view globalName, Type& type, const GlobalArgs& args) const {
            const auto fullName = nameFor(globalName);
            const auto create = [&]() -> function_ref<GlobalVariable*()> {
                if (args.module) {
                    return new GlobalVariable(
                            *args.module,
                            &type,
                            args.isConstant,
                            args.linkage,
                            &args.initializer,
                            fullName,
                            args.insertBefore,
                            args.threadLocalMode,
                            args.addressSpace,
                            args.isExternallyInitialized
                    );
                } else {
                    return new GlobalVariable(
                            &type,
                            args.isConstant,
                            args.linkage,
                            &args.initializer,
                            fullName,
                            args.threadLocalMode,
                            args.addressSpace,
                            args.isExternallyInitialized
                    );
                }
            }();
            return *module.getOrInsertGlobal(fullName, &type, create);
        }
        
        template <typename T>
        Constant& global(std::string_view globalName) const {
            return global(globalName, &types.get<T>());
        }
        
        template <typename T>
        Constant& global(std::string_view globalName, const GlobalArgs& args) const {
            return global(globalName, &types.get<T>(), args);
        }
        
    };
    
}
