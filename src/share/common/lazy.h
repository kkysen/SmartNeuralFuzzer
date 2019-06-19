//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include <memory>
#include <optional>

template <typename T>
class LazilyConstructed {

private:
    
    static constexpr T* notCreated = nullptr;
    static T* destructed;
    
    mutable T* instance = notCreated;

public:
    
    constexpr LazilyConstructed() noexcept = default;
    
    constexpr bool exists() const noexcept {
        return __builtin_expect(instance > destructed, true);
    }
    
    constexpr bool isDestructed() const noexcept {
        return __builtin_expect(instance == destructed, false);
    }
    
    explicit constexpr operator bool() const noexcept {
        return exists();
    }
    
    void destruct() const {
        delete instance;
        instance = destructed;
    }
    
    void reconstruct() const {
        if (exists()) {
            destruct();
        }
        instance = new T();
    }
    
    bool constructed() const {
        const bool constructed = !exists();
        if (constructed) {
            reconstruct();
        }
        return constructed;
    }
    
    void construct() const {
        constructed();
    }
    
    T& get() const {
        construct();
        return *instance;
    }
    
    T& operator()() const {
        return get();
    }
    
    T& operator*() const {
        return get();
    }
    
    T* operator->() const {
        return &get();
    }
    
    template <class F>
    auto apply(F f) noexcept(noexcept(f(T()))) -> std::optional<decltype(f(T()))> {
        if (exists()) {
            return f(get());
        } else {
            return nullptr;
        }
    }
    
};

template <typename T>
T* LazilyConstructed<T>::destructed = reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(nullptr) + 1);

template <class F = void (*)()>
class RunOnce {

private:
    
    F f;
    bool ran = false;

public:
    
    /*implicit*/ constexpr RunOnce(F f) noexcept : f(f) {
        if (!ran) {
            ran = true;
            f();
        }
    }
    
};
