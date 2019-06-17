//
// Created by Khyber on 6/17/2019.
//

#include "src/share/io/env/Exec.h"

namespace env {
    
    Exec::Exec(int fd) : fd(fd) {
        if (fd < 0) {
            fse::_throw(fse::error("Exec(fd = " + std::to_string(fd) + ")"));
        }
    }
    
    void Exec::_print(std::ostream& out) const {
        out << (!path ? "fexecve" : (isPath ? "execve" : "execvpe"));
        out << "(";
        if (!path) {
            out << fd;
        } else {
            out << path;
        }
        out << ", {";
        if (!_argv.empty()) {
            out << _argv[0];
        }
        for (size_t i = 1; i < _argv.size(); i++) {
            const auto arg = _argv[i];
            if (arg) {
                out << ", " << arg;
            }
        }
        out << "})";
        out << std::endl;
        // env is too big, can't print it
    }
    
    const Exec& Exec::print(std::ostream& out) const {
        _print(out);
        return *this;
    }
    
    Exec& Exec::print(std::ostream& out) {
        _print(out);
        return *this;
    }
    
    void Exec::ensureArgvNullTerminated() const {
        if (argv().back() != nullptr) {
            const_cast<Exec&>(*this).argv().emplace_back(nullptr);
        }
    }
    
    int Exec::execReturn(const Environment& env) const noexcept {
        ensureArgvNullTerminated();
        const auto envp = const_cast<char* const*>(env.asEnviron());
        const auto argv = const_cast<char* const*>(_argv.data());
        if (!path) {
            return ::fexecve(fd, argv, envp);
        } else {
            return (isPath ? ::execve : ::execvpe)(path, argv, envp);
        }
    }
    
    void Exec::exec(const Environment& env) const {
        if (execReturn(env) == -1) {
            std::stringstream ss;
            print(ss);
            fse::_throw(fse::error(ss.str()));
        }
    }
    
    void Exec::operator()(const Environment& env) const {
        exec(env);
    }
    
}
