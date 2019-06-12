//
// Created by Khyber on 6/3/2019.
//

#pragma once

#include <condition_variable>

namespace concurrent {
    
    struct ConditionVariable {
        
        std::mutex mutex; // it's annoying I can't use an adaptive mutex for this
        std::condition_variable cv;
        
        void wait();
        
        template <class Predicate>
        void wait(Predicate predicate) {
            std::unique_lock lock(mutex);
            cv.wait(lock, predicate);
        }
        
        template <class Repr, class Period>
        std::cv_status waitFor(const std::chrono::duration<Repr, Period>& timeout) {
            std::unique_lock lock(mutex);
            return cv.wait_for(lock, timeout);
        }
        
        template <class Repr, class Period, class Predicate>
        bool waitFor(const std::chrono::duration<Repr, Period>& timeout, Predicate predicate) {
            std::unique_lock lock(mutex);
            return cv.wait_for(lock, timeout, predicate);
        }
        
        template <class Clock, class Duration>
        std::cv_status waitUntil(const std::chrono::time_point<Clock, Duration>& timeout) {
            std::unique_lock lock(mutex);
            return cv.wait_until(lock, timeout);
        }
        
        template <class Clock, class Duration, class Predicate>
        bool waitUntil(const std::chrono::time_point<Clock, Duration>& timeout, Predicate predicate) {
            std::unique_lock lock(mutex);
            return cv.wait_until(lock, timeout, predicate);
        }
        
        void notifyOne() noexcept;
        
        void notifyAll() noexcept;
        
        class Waiter {

        private:
            
            ConditionVariable& cv;

        public:
            
            explicit constexpr Waiter(ConditionVariable& cv) noexcept : cv(cv) {}
    
            void wait();
    
            template <class Predicate>
            void wait(Predicate predicate) {
                cv.wait(predicate);
            }
    
            template <class Repr, class Period>
            std::cv_status waitFor(const std::chrono::duration<Repr, Period>& timeout) {
                return cv.waitFor(timeout);
            }
    
            template <class Repr, class Period, class Predicate>
            bool waitFor(const std::chrono::duration<Repr, Period>& timeout, Predicate predicate) {
                return cv.waitFor(timeout, predicate);
            }
    
            template <class Clock, class Duration>
            std::cv_status waitUntil(const std::chrono::time_point<Clock, Duration>& timeout) {
                return cv.waitUntil(timeout);
            }
    
            template <class Clock, class Duration, class Predicate>
            bool waitUntil(const std::chrono::time_point<Clock, Duration>& timeout, Predicate predicate) {
                return cv.waitUntil(timeout, predicate);
            }
            
        };
    
        class Notifier {
    
        private:
        
            ConditionVariable& cv;
    
        public:
        
            explicit constexpr Notifier(ConditionVariable& cv) noexcept : cv(cv) {}
    
            void notifyOne() noexcept;
    
            void notifyAll() noexcept;
            
        };
        
        constexpr Waiter waiter() noexcept {
            return Waiter(*this);
        }
    
        constexpr Notifier notifier() noexcept {
            return Notifier(*this);
        }
        
    };
    
}
