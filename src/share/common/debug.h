//
// Created by Khyber on 2/28/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/hook/libc/syscall/getpid.h"
#include "src/share/hook/libc/syscall/gettid.h"

#include <string_view>
#include <iostream>
#include <sstream>
#include <array>
#include <fstream>

#include <csignal>
#include <cstring>

namespace debug {
    
    extern bool mode;
    
    extern std::ostream* out;
    
    extern bool reversed;
    
    class Indentation {
    
    public:
        
        static char defaultChar;
        static size_t defaultIndent;
    
    private:
        
        size_t _size;
        std::string string;
        
        void syncString();
    
    public:
        
        explicit Indentation(size_t size = 0) noexcept;
        
        constexpr size_t size() const noexcept {
            return _size;
        }
        
        constexpr std::string_view get() const noexcept {
            return string;
        }
        
        void indent(size_t indent = defaultIndent);
        
        void unIndent(size_t indent = defaultIndent);
        
    };
    
    extern Indentation indentation;
    
    class Indented {
    
    private:
        
        Indentation& indentation;
    
    public:
        
        explicit Indented(Indentation& indentation = debug::indentation);
        
        ~Indented();
        
    };
    
    struct Info {
        std::string_view funcName;
        std::string_view fileName;
        u64 lineNum;
    };
    
    using ErrorNumToString = const char* (*)(int);
    
    struct ErrorInfo : public Info {
        
        static const char* strerror(int errorNum);
        
        int errorNum;
        ErrorNumToString errorNumToString;
        
        constexpr ErrorInfo(Info info, int errorNum, ErrorNumToString errorNumToString) noexcept
                : Info(info), errorNum(errorNum), errorNumToString(errorNumToString) {}
        
        explicit ErrorInfo(Info info) noexcept;
        
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
                threadId(!mode ? 0 : syscalls::gettid()),
                processId(!mode ? 0 : syscalls::getpid()) {}
    
    private:
        
        class Printer {
        
        private:
            
            const Debug& debug;
        
        public:
            
            explicit constexpr Printer(const Debug& debug) noexcept : debug(debug) {}
            
            constexpr OutputStream& out() const noexcept {
                return debug.out;
            }
            
            void space() {
                if (debug.mode) {
                    out() << " ";
                }
            }
            
            void processId() {
                if (debug.mode) {
                    out() << "[pid=" << debug.processId << "]";
                }
            }
            
            void threadId() {
                if (debug.mode) {
                    out() << "[tid=" << debug.threadId << "]";
                }
            }
            
            void id() {
                processId();
                threadId();
            }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
            
            void location() {
                if (debug.mode) {
                    const auto& info = debug.info;
                    out() << "(" << info.funcName << " at " << info.fileName << ":" << info.lineNum << ")";
                }
            }
            
            void errorNum() {
                if (debug.mode) {
                    const auto& info = debug.info;
                    out() << "[errno=" << info.errorNum << "]";
                }
            }
            
            void errorMessage() {
                if (debug.mode) {
                    const auto& info = debug.info;
                    out() << "(" << info.errorNumToString(info.errorNum) << ")";
                }
            }

#pragma clang diagnostic pop
            
            void error() {
                errorNum();
                space();
                errorMessage();
            }
            
            void idLocation() {
                id();
                space();
                location();
            }
            
            template <typename T>
            Printer& operator<<(const T& t) {
                if (debug.mode) {
                    out() << t;
                }
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
                      << std::string(sizeof(std::string) - 2, ' ');
                if (printError) {
                    print << ": ";
                    print.error();
                }
                print.idLocation();
            }
            print << "\n";
            out.flush();
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
            if constexpr (std::is_pointer_v<T> && !std::is_same_v<T, const char*>) {
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
            out.flush();
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

#define debug_info() (debug::Info { \
    .funcName = __func__, \
    .fileName = __FILE__, \
    .lineNum = __LINE__, \
})

#define debug_errorInfo() debug::ErrorInfo(debug_info())

#define _debug(out) debug::Debug(out, debug_errorInfo())

#define _expr(expr) debug::Expression(""#expr, expr)

#define _dbg(expr) _debug(*debug::out)(_expr(expr))
