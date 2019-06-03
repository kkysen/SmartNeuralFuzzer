//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include "src/share/aio/signal/Value.h"

#include <string_view>

#include <ctime>

namespace aio::signal {
    
    struct Info {
        
        struct {
            
            int signal;
            int error;
            int code;
            #ifdef si_trapno
            int trapNumber;
            #endif
            
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
                    Value value;
                } timer;
                
                // Posix.1b signals
                struct {
                    pid_t pid;
                    uid_t uid;
                    Value value;
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
                        #ifdef si_pkey
                        u32 protectionKey;
                        #endif
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
                
            } __SI_ALIGNMENT;
            
        };
        
        // could be constexpr and implicit conversions if I copy the fields
        // constexpr might be able to help remove the copy
        // not using reinterpret_cast would certainly be safer,
        // b/c I'm not even sure if these fields are always arranged this way
        // also, si_trapno seems to be missing from the implementations I've looked at
        
        static const Info& of(const siginfo_t& info) noexcept;
        
        static Info& of(siginfo_t& info) noexcept;
        
        const siginfo_t& impl() const noexcept;
        
        siginfo_t& impl() noexcept;
        
        /*implicit*/ operator const siginfo_t&() const noexcept;
        
        /*implicit*/ operator siginfo_t&() noexcept;
    
        static Info value(int code, const Value& value) noexcept;
        
    private:
        
        static constexpr std::pair<bool, std::string_view> memoryLayoutMatchesSigInfoT(
                const siginfo_t& sigInfo, const Info& info) noexcept {
            std::string_view message;
            #define assert(expr) (message = ""#expr, expr)
            
            #define _(siginfo_t_field, Info_field) && assert(sigInfo.si_##siginfo_t_field == info.Info_field)
            
            const bool matches = true
                                 _(signo, signal)
                                 _(errno, error)
                                 _(code, code)
                                 #ifdef si_trapno
                                 _(trapno, trapNumber)
                                 #endif
                                 _(pid, killer.pid)
                                 _(uid, killer.uid)
                                 _(status, child.status)
                                 _(utime, child.timeConsumed.user)
                                 _(stime, child.timeConsumed.system)
                                 //_(value, rt.value)
                                 // can't compare sigval_t's,
                                 // but the two below checks check the individual fields
                                 _(int, rt.value.get<int>())
                                 _(ptr, rt.value.raw.ptr)
                                 _(overrun, timer.overrunCount)
                                 _(timerid, timer.id)
                                 _(addr, fault.address.value)
                                 _(band, poll.band)
                                 _(fd, poll.fd)
                                 _(addr_lsb, fault.address.lsb)
                                 _(lower, fault.bound.address.lower)
                                 _(upper, fault.bound.address.upper)
                                 #ifdef si_pkey
                                 _(pkey, fault.bound.protectionKey)
                                 #endif
                                 _(call_addr, syscall.callAddress)
                                 _(syscall, syscall.number)
                                 _(arch, syscall.arch);
            
            #undef _
            
            return {matches, message};
        }
        
        static std::pair<bool, std::string_view> memoryLayoutMatchesSigInfoT(size_t trials) noexcept;
    
    public:
        
        static bool checkMemoryLayoutMatchesSigInfoT(size_t trials = 1000);
        
    };
    
    static_assert(sizeof(Info) == sizeof(siginfo_t));
    
}
