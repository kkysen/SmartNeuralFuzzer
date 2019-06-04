//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include <csignal>

extern "C"
int rt_sigqueueinfo(pid_t tgid, int signal, siginfo_t* info) noexcept;

extern "C"
int rt_tgsigqueueinfo(pid_t tgid, pid_t tid, int signal, siginfo_t* info) noexcept;
