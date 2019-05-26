//
// Created by Khyber on 5/25/2019.
//

#pragma once

#include "src/share/common/numbers.h"

#include <csignal>

namespace aio::signal {
    
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
    
}
