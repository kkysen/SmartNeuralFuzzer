//
// Created by Khyber on 6/4/2019.
//

#include "src/share/hook/libc/hooksImpl/include.h"
#include "src/share/hook/libc/hooksImpl/Wrapped.h"

extern "C"
pid_t fork() noexcept {
    trace();
    const auto cpid = impl::fork();
    if (cpid != -1) {
        onProcessConstruction(cpid);
    }
    return cpid;
}

extern "C"
pid_t vfork() noexcept {
    trace();
    const auto cpid = impl::vfork();
    if (cpid != -1) {
        onProcessConstruction(cpid); // TODO is this necessary
    }
    return cpid;
}

extern "C"
int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void* (* startRoutine)(void*), void* arg) noexcept {
    trace();
    hook::libc::Wrapped<void*, onThreadConstruction> wrapped(startRoutine, arg);
    return impl::pthread_create(thread, attr, wrapped.f, wrapped.arg());
}
