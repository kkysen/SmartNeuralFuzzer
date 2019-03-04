//
// Created by Khyber on 2/28/2019.
//

#pragma once


#include <string_view>
#include <signal.h>
#include <iostream>
#include <sstream>
#include "llvm/Support/raw_ostream.h"
#include <unistd.h>
#include <syscall.h>
#include "llvm/IR/BasicBlock.h"
#include "numbers.h"

namespace debug {
    
    bool mode = true;
    
    auto out = &std::cerr;
    
    bool reversed = false;
    
    class Indentation {
    
    public:
        
        static char defaultChar;
        static size_t defaultIndent;
    
    private:
        
        size_t _size;
        std::string string;
        
        void syncString() {
            string.resize(_size, defaultChar);
        }
    
    public:
        
        explicit Indentation(size_t size = 0) noexcept
                : _size(size), string() {}
        
        constexpr size_t size() const noexcept {
            return _size;
        }
        
        constexpr std::string_view get() const noexcept {
            return string;
        }
        
        void indent(size_t indent = defaultIndent) {
            _size += indent;
            syncString();
        }
        
        void unIndent(size_t indent = defaultIndent) {
            if (_size < indent) {
                _size = 0;
            } else {
                _size -= indent;
            }
            syncString();
        }
        
    };
    
    char Indentation::defaultChar = ' ';
    size_t Indentation::defaultIndent = 4;
    
    Indentation indentation;
    
    class Indented {
    
    private:
        
        Indentation& indentation;
    
    public:
        
        explicit Indented(Indentation& indentation = debug::indentation) : indentation(indentation) {
            indentation.indent();
        }
        
        ~Indented() {
            indentation.unIndent();
        }
        
    };
    
    struct Info {
        std::string_view funcName;
        std::string_view fileName;
        u64 lineNum;
    };
    
    using ErrorNumToString = const char* (*)(int);
    
    struct ErrorInfo : public Info {
        
        static const char* strerror(int errorNum) {
            return ::strerror(errorNum);
        }
        
        int errorNum;
        ErrorNumToString errorNumToString;
        
        constexpr ErrorInfo(Info info, int errorNum, ErrorNumToString errorNumToString) noexcept
                : Info(info), errorNum(errorNum), errorNumToString(errorNumToString) {}
        
        explicit ErrorInfo(Info info) noexcept : ErrorInfo(info, errno, strerror) {}
        
    };
    
    template <typename T>
    struct Expression {
        
        std::string_view name;
        const T& expression;
        
        constexpr Expression(std::string_view name, const T& expression) noexcept
                : name(name), expression(expression) {}
        
    };
    
    template <class OutputStream>
    class Debug {
    
    public:
        
        OutputStream& out;
        
        const ErrorInfo info;
        
        const bool mode;
        
        const pid_t threadId = 0;
        const pid_t processId = 0;
        
        explicit Debug(OutputStream& out, ErrorInfo info, bool mode = debug::mode) noexcept :
                out(out),
                info(info),
                mode(mode),
                threadId(!mode ? 0 : static_cast<pid_t>(syscall(SYS_gettid))),
                processId(!mode ? 0 : getpid()) {}
    
    private:
        
        class Printer {
        
        private:
            
            const Debug& debug;
        
        public:
            
            explicit constexpr Printer(const Debug& debug) noexcept : debug(debug) {}
            
            constexpr OutputStream& out() const noexcept {
                return debug.out;
            }
            
            void processId() {
                out() << "[pid=" << debug.processId << "]";
            }
            
            void threadId() {
                out() << "[tid=" << debug.threadId << "]";
            }
            
            void id() {
                processId();
                threadId();
            }
            
            void location() {
                const auto& info = debug.info;
                out() << "(" << info.funcName << " at " << info.fileName << ":" << info.lineNum << ")";
            }
            
            void errorNum() {
                const auto& info = debug.info;
                out() << "[errno=" << info.errorNum << "]";
            }
            
            void errorMessage() {
                const auto& info = debug.info;
                out() << "(" << info.errorNumToString(info.errorNum) << ")";
            }
            
            void error() {
                errorNum();
                out() << " ";
                errorMessage();
            }
            
            void idLocation() {
                id();
                out() << " ";
                location();
            }
            
            template <typename T>
            Printer& operator<<(const T& t) {
                out() << t;
                return *this;
            }
            
        };
    
    public:
        
        constexpr Printer printer() const noexcept {
            return Printer(*this);
        }
    
    private:
        
        void message2(std::string_view message1, std::string_view message2, bool printError = true) const noexcept {
            auto print = printer();
            if (!reversed) {
                print.idLocation();
                print << ": " << indentation.get() << message1 << message2;
                if (printError) {
                    print << ": ";
                    print.error();
                }
            } else {
                print << indentation.get()
                      << message1 << message2
                      << std::string(22, ' ');
                if (printError) {
                    print << ": ";
                    print.error();
                }
                print.idLocation();
            }
            print << "\n";
        }
    
    public:
        
        void function(std::string_view throwingFuncName) const noexcept {
            message2(throwingFuncName, "() failed");
        }
        
        void functionCall(std::string_view throwingFuncCall) const noexcept {
            message2(throwingFuncCall, " failed");
        }
        
        void message(std::string_view message) const noexcept {
            message2(message, "", false);
        }
        
        template <typename T>
        void expression(Expression<T> expr) const noexcept {
            if constexpr (std::is_pointer_v<T>) {
                return expression<std::remove_pointer_t<T>>(Expression(expr.name, *expr.expression));
            }
            auto print = printer();
            if (!reversed) {
                print.idLocation();
                print << indentation.get()
                      << " " << expr.name
                      << ": " << expr.expression;
            } else {
                print << indentation.get()
                      << " " << expr.name
                      << ": " << expr.expression
                      << std::string(22, ' ');
                print.idLocation();
            }
            print << "\n";
        }
        
        template <typename T>
        void operator()(Expression<T> expr) const noexcept {
            expression(expr);
        }
        
        template <typename T>
        void expression(std::string_view name, const T& object) const noexcept {
            expression({.name = name, .object = object});
        }
        
    };
    
}

namespace llvm {
    
    raw_ostream& operator<<(raw_ostream& out, bool boolean) {
        return out << (boolean ? "true" : "false");
    }
    
    raw_ostream& operator<<(raw_ostream& out, std::string_view view) {
        return out << StringRef(view.data(), view.size());
    }
    
    std::string_view to_string_view(Type::TypeID typeId) {
        switch (typeId) {
            case Type::VoidTyID:
                return "void";
            case Type::HalfTyID:
                return "half";
            case Type::FloatTyID:
                return "float";
            case Type::DoubleTyID:
                return "double";
            case Type::X86_FP80TyID:
                return "x86_fp80";
            case Type::FP128TyID:
                return "fp128";
            case Type::PPC_FP128TyID:
                return "ppc_fp128";
            case Type::LabelTyID:
                return "label";
            case Type::MetadataTyID:
                return "metadata";
            case Type::X86_MMXTyID:
                return "x86_mmx";
            case Type::TokenTyID:
                return "token";
            case Type::IntegerTyID:
                return "integer";
            
            
            case Type::FunctionTyID:
                return "function";
            case Type::StructTyID:
                return "struct";
            case Type::PointerTyID:
                return "pointer";
            case Type::ArrayTyID:
                return "array";
            case Type::VectorTyID:
                return "vector";
        }
        auto invalid = "Invalid TypeID (" + std::to_string(static_cast<size_t>(typeId)) + ")";
        llvm_unreachable(invalid.c_str());
    }
    
    raw_ostream& operator<<(raw_ostream& out, Type::TypeID typeId) {
        return out << to_string_view(typeId);
    }
    
    std::string uuid(BasicBlock& block) {
        std::string s;
        raw_string_ostream out(s);
        block.printAsOperand(out, false);
        return out.str();
    }
    
}

#define debug_info() (debug::Info { \
    .funcName = __func__, \
    .fileName = __FILE__, \
    .lineNum = __LINE__, \
})

#define debug_errorInfo() debug::ErrorInfo(debug_info())

#define _debug(out) debug::Debug(out, debug_errorInfo())

#define _expr(expr) debug::Expression(""#expr, expr)

#define _dbg(expr) _debug(*debug::out)(_expr(expr))

#define llvm_debug() _debug(llvm::errs())

#define llvm_dbg(expr) llvm_debug()(_expr(expr))