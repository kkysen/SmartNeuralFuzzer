//
// Created by Khyber on 6/4/2019.
//

#include "src/share/capability/Header.h"

#include "src/share/hook/libc/syscall/cap.h"
#include "src/share/hook/libc/syscall/getpid.h"

namespace capability {
    
    const Header::Impl& Header::impl() const noexcept {
        return reinterpret_cast<const Impl&>(*this);
    }
    
    Header::Impl& Header::impl() noexcept {
        return reinterpret_cast<Impl&>(*this);
    }
    
    Header::operator const Impl&() const noexcept {
        return impl();
    }
    
    Header::operator Impl&() noexcept {
        return impl();
    }
    
    Header::Header() noexcept : Header(syscalls::getpid()) {}
    
    Header::Impl& Header::mut() const noexcept {
        return const_cast<Impl&>(impl());
    }
    
    bool Header::get(__user_cap_data_struct* data) const noexcept {
        return syscalls::capget(&mut(), data) == 0;
    }
    
    bool Header::set(const __user_cap_data_struct* data) const noexcept {
        return syscalls::capset(&mut(), data) == 0;
    }
    
}
