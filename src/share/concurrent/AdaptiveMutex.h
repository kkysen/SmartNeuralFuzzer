//
// Created by Khyber on 5/31/2019.
//

#pragma once

#include "src/share/concurrent/SpinLock.h"
#include "src/share/concurrent/numVirtualCores.h"
#include "src/share/concurrent/Mutex.h"

#include <mutex>

namespace concurrent {
    
    template <class Mutex = concurrent::Mutex>
    class AdaptiveMutex {
    
    private:
        
        using Clock = std::chrono::steady_clock;
        using Time = typename Clock::duration::rep;
        using AtomicTime = std::atomic<Time>;
        static_assert(AtomicTime::is_always_lock_free);
        
        // I've since realized that std::mutex, which uses pthread_mutex,
        // does in fact use an adaptive mutex,
        // so this is mostly for nothing,
        // and the pthread version is likely much more optimized
        static const size_t getTimeCycles = 0; // for now
        
        SpinLock spin;
        Mutex mutex;
        AtomicTime predictedTime = 0;
    
    public:
        
        void unlock() noexcept {
            mutex.unlock();
            spin.unlock();
        }
        
        bool tryLock() noexcept {
            return isSingleThreaded() ? mutex.try_lock() : spin.tryLock();
        }
        
        bool try_lock() noexcept {
            return tryLock();
        }
    
    private:
        
        void singleThreadedLock() noexcept {
            mutex.lock();
        }
        
        bool countSpinLock() noexcept {
            size_t count = 0;
            while (!spin.tryLock() && ++count < getTimeCycles) {}
            return count < getTimeCycles;
        }
        
        bool timedSpinLock() noexcept {
            if (countSpinLock()) {
                return true;
            }
            const auto start = Clock::now();
            bool locked = true;
            Time elapsed = 0;
            while (!countSpinLock()) {
                elapsed = (Clock::now() - start).count();
                if (elapsed >= predictedTime * 2) {
                    locked = false;
                    break;
                }
            }
            // https://hackernoon.com/building-a-c-hybrid-spin-mutex-f98de535b4ac
            // https://stackoverflow.com/questions/19863734/what-is-pthread-mutex-adaptive-np
            predictedTime += (elapsed - predictedTime) / 8;
            return locked;
        }
        
        void multiThreadedLock() noexcept {
            if (!timedSpinLock()) {
                mutex.lock();
            }
        }
    
    public:
        
        void lock() noexcept {
            isSingleThreaded() ? singleThreadedLock() : multiThreadedLock();
        }
        
    };
    
    #ifdef PTHREAD_ADAPTIVE_MUTEX_INITIALIZER_NP
    
    template <>
    class AdaptiveMutex<Mutex> {
    
    private:
        
        Mutex mutex = {Mutex::Init::adaptive};
    
    public:
        
        void unlock() noexcept {
            mutex.unlock();
        }
        
        bool tryLock() noexcept {
            return mutex.try_lock();
        }
        
        bool try_lock() noexcept {
            return tryLock();
        }
        
        void lock() noexcept {
            mutex.lock();
        }
        
    };
    
    template <>
    class AdaptiveMutex<std::mutex> : public AdaptiveMutex<Mutex> {};
    
    #endif
    
}
