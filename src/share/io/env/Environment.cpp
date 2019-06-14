//
// Created by Khyber on 6/14/2019.
//

#include "src/share/io/env/Environment.h"

#include "src/share/stde/addStrings.h"

#include "llvm/ADT/Twine.h"

namespace {
    
    using llvm::convert::ref;
    
    using namespace std::literals;
    using stde::string::operator+;
    
}

namespace env {
    
    Environment::Environment(const char* const* _environ) {
        const char* rawVarValue;
        while ((rawVarValue = *_environ++)) {
            const std::string_view varValueView = rawVarValue;
            const auto i = findDelimiter(varValueView);
            if (i == std::string_view::npos) {
                continue; // silently ignore errors
            }
            insert(varValueView, i, true);
        }
        environ.push_back(nullptr); // environ must be null-terminated
    }
    
    bool Environment::has(std::string_view var) const noexcept {
        return vars.count(ref(var)) > 0;
    }
    
    std::string_view Environment::get(std::string_view var) const noexcept {
        const auto it = vars.find(ref(var));
        if (it == vars.end()) {
            return {};
        }
        return it->second.second;
    }
    
    std::string_view Environment::operator[](std::string_view var) const noexcept {
        return get(var);
    }
    
    void Environment::setHard(std::string_view var, std::string_view value) {
        insert(""s + var + delimiter + value, var.size());
    }
    
    bool Environment::trySet(std::string_view var, std::string_view value) {
        const bool set = !has(var);
        if (set) {
            setHard(var, value);
        }
        return set;
    }
    
    bool Environment::set(std::string_view var, std::string_view value) {
        const bool override = has(var);
        if (override) {
            modify(var, override, [=](std::string& oldValue) {
                oldValue = value;
            });
        } else {
            setHard(var, value);
        }
        return override;
    }
    
    bool Environment::unSet(std::string_view var) {
        const auto it = vars.find(ref(var));
        const bool unSet = it != vars.end();
        if (unSet) {
            const auto [i, _] = it->second;
            vars.erase(it);
            store.erase(store.begin() + i);
            environ.erase(environ.begin() + i);
        }
        return unSet;
    }
    
    bool Environment::append(std::string_view var, std::string_view addition, std::string_view valueDelimiter) {
        const bool override = has(var);
        if (override) {
            modify(var, override, [=](std::string& value) {
                value += valueDelimiter;
                value += addition;
            });
        } else {
            setHard(var, addition);
        }
        return override;
    }
    
}
