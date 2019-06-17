//
// Created by Khyber on 6/14/2019.
//

#pragma once

#include "src/share/llvm/lib/conversions.h"
#include "src/share/io/fse.h"

#include "llvm/ADT/StringMap.h"

#include <unistd.h>

namespace env {
    
    using Environ = const char* const*;
    
    class Environment {
    
    private:
        
        static constexpr std::string_view delimiter = "=";
        
        Environ unmodified;
        llvm::StringMap<std::pair<size_t, std::string_view>> vars;
        llvm::SmallVector<std::string, 0> store;
        llvm::SmallVector<const char*, 0> environ;
        
        static constexpr size_t findDelimiter(std::string_view varValue) noexcept {
            if constexpr (delimiter.size() == 1) {
                return varValue.find(delimiter[0]);
            } else {
                return varValue.find(delimiter);
            }
        }
        
        template <class StringArg>
        void insert(StringArg&& varValueToAdd, size_t varSize, bool bulkInsertion = false) {
            store.emplace_back(std::forward<StringArg>(varValueToAdd));
            const std::string& varValueStore = store.back();
            const std::string_view varValue = varValueStore; // stable pointer
            const auto var = varValue.substr(0, varSize);
            const auto value = varValue.substr(varSize + 1);
            using llvm::convert::ref;
            const auto[_, inserted] = vars.try_emplace(ref(var), store.size() - 1, value);
            if (!inserted) {
                store.pop_back();
            }
            auto insertionPoint = environ.end();
            if (!bulkInsertion) {
                insertionPoint--;
            }
            environ.insert(insertionPoint, varValueStore.c_str());
        }
    
        void init(Environ environ);
        
        void init() const;
        
    public:
        
        explicit Environment(Environ _environ = ::environ);
        
        static Environment empty();
        
        constexpr Environ asEnviron() const noexcept {
            return environ.data();
        }
        
        /*implicit*/ constexpr operator Environ() const noexcept {
            return unmodified ? unmodified : asEnviron();
        }
        
        bool has(std::string_view var) const noexcept;
    
        std::string_view get(std::string_view var, std::string_view defaultValue) const noexcept;
        
        std::string_view get(std::string_view var) const noexcept;
        
        std::string_view operator[](std::string_view var) const noexcept;
    
    private:
        
        // assume !has(var)
        void setHard(std::string_view var, std::string_view value);
        
        template <class F>
        void modify(std::string_view var, bool override, F modify) {
            if (!override) {
                setHard(var, "");
            }
            using llvm::convert::ref;
            auto& indexAndOldValue = vars[ref(var)];
            const auto i = indexAndOldValue.first;
            auto& oldValue = indexAndOldValue.second;
            auto& valueStore = store[i];
            modify(valueStore);
            oldValue = valueStore;
            environ[i] = valueStore.c_str();
        }
    
    public:
        
        // call modify(std::string& oldValue)
        // if there's no old value, then "" is used
        template <class F>
        bool modify(std::string_view var, F f) {
            const bool override = has(var);
            modify(var, override, f);
            return override;
        }
        
        bool trySet(std::string_view var, std::string_view value);
        
        bool set(std::string_view var, std::string_view value);
        
        bool unSet(std::string_view var);
        
        bool append(std::string_view var, std::string_view addition, std::string_view delimiter);
        
        std::string toString() const;
        
    };
    
}
