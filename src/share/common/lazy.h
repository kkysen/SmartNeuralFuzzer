//
// Created by Khyber on 3/22/2019.
//

#pragma once

#include <memory>
#include <optional>

template <typename T>
class LazilyConstructed {

private:
    
    mutable std::unique_ptr<T> instance = nullptr;

public:
    
    constexpr LazilyConstructed() noexcept = default;
    
    void reconstruct() const {
        instance = std::make_unique<T>();
    }
    
    constexpr bool exists() const noexcept {
        return static_cast<bool>(instance);
    }
    
    explicit constexpr operator bool() const noexcept {
        return exists();
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
    
    void destruct() const {
        instance = nullptr;
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