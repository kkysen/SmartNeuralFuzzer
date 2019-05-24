//
// Created by Khyber on 5/24/2019.
//

#pragma once

#include <ostream>

#include <csignal>
#include <src/share/common/numbers.h>

namespace aio {
    
    class Signal {
    
    public:
        
        struct Info {
            
            int signal;
            int error;
            int code;
//            int trapNumber;
            
            union {
                
                int _padding[__SI_PAD_SIZE];
    
                // kill()
                struct {
                    pid_t pid;
                    uid_t uid;
                } killer;
    
                // Posix.1b timers
                struct {
                    int id;
                    int overrunCount;
                    sigval_t value;
                } timer;
    
                // Posix.1b signals
                struct {
                    pid_t pid;
                    uid_t uid;
                    sigval_t value;
                } rt;
    
                // SIGCHLD
                struct {
                    pid_t pid;
                    uid_t uid;
                    int status;
                    struct {
                        clock_t user;
                        clock_t system;
                    } timeConsumed;
                } child;
    
                // SIGILL, SIGFPE, SIGSEGV, SIGBUS
                struct {
                    struct {
                        void* value;
                        short lsb;
                    } address;
                    union {
                        struct {
                            void* lower;
                            void* upper;
                        } address;
                        u32 protectionKey;
                    } bound;
                } fault;
    
                // SIGPOLL
                struct {
                    long band;
                    int fd;
                } poll;
    
                // SIGSYS
                struct {
                    void* callAddress;
                    int number;
                    unsigned int arch;
                } syscall;
                
            };
            
            // could be constexpr and implicit conversions if I copy the fields
            // constexpr might be able to help remove the copy
            // not using reinterpret_cast would certainly be safer,
            // b/c I'm not even sure if these fields are always arranged this way
            // also, si_trapno seems to be missing from the implementations I've looked at
            
            static const Info& of(const siginfo_t& info) noexcept;
        
            static Info& of(siginfo_t& info) noexcept;
            
            /*implicit*/ operator const siginfo_t&() const noexcept;
        
            /*implicit*/ operator siginfo_t&() noexcept;
            
        };
        
        struct ConstContext {
            
            const ucontext_t& impl;
            
            /*implicit*/ constexpr ConstContext(const ucontext_t& impl) noexcept : impl(impl) {}
            
            /*implicit*/ constexpr operator const ucontext_t&() const noexcept {
                return impl;
            }
    
            constexpr const ucontext_t& linkRaw() const noexcept {
                return *impl.uc_link;
            };
            
            constexpr ConstContext link() const noexcept {
                return linkRaw();
            }
    
            #define field(T, name, implName) \
            constexpr const T& name() const noexcept { \
                return impl.implName; \
            } \
            
            #define fields() \
            field(sigset_t, mask, uc_sigmask) \
            field(stack_t, stack, uc_stack) \
            field(mcontext_t, machineContext, uc_mcontext) \
            
            fields()
    
            #undef field
            
        };
        
        // impl dependent, so need to wrap impl ptr
        struct Context {
        
            ucontext_t& impl;
            
            /*implicit*/ constexpr Context(ucontext_t& impl) noexcept : impl(impl) {}
            
            /*implicit*/ constexpr operator ucontext_t&() noexcept {
                return impl;
            }
            
            constexpr const ucontext_t& linkRaw() const noexcept {
                return *impl.uc_link;
            };
            
            constexpr ucontext_t& linkRaw() noexcept {
                return *impl.uc_link;
            }
            
            constexpr ConstContext link() const noexcept {
                return linkRaw();
            }
    
            constexpr Context link() noexcept {
                return linkRaw();
            }
    
            #define field(T, name, implName) \
            constexpr const T& name() const noexcept { \
                return impl.implName; \
            } \
            constexpr T& name() noexcept { \
                return impl.implName; \
            } \
            
            fields()
    
            #undef field
            #undef fields
            
        };
        
        int signal;
        const Info& info;
        ConstContext context;
        
        constexpr Signal(int signal, const Info& info, ConstContext context) noexcept
                : signal(signal), info(info), context(context) {}
        
        // could be constexpr, see Info::of()
        Signal(int signal, const siginfo_t* sigInfo, const void* context) noexcept;
        
    };
    
}