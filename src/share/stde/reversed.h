//
// Created by Khyber on 5/24/2019.
//

#pragma once

namespace stde {
    
    template <class Container>
    class ReversedIterable {

    private:
    
        Container& impl;
    
    public:
    
        explicit constexpr ReversedIterable(Container& impl) noexcept : impl(impl) {}
        
        using const_iterator = typename Container::const_reverse_iterator;
        using iterator = typename Container::reverse_iterator;
        
        using const_reverse_iterator = typename Container::const_iterator;
        using reverse_iterator = typename Container::iterator;
        
        
        
        const_iterator begin() const noexcept {
            return impl.rbegin();
        }
        
        iterator begin() noexcept {
            return impl.rbegin();
        }
        
        const_iterator cbegin() const noexcept {
            return impl.crbegin();
        }
    
        const_iterator end() const noexcept {
            return impl.rend();
        }
    
        iterator end() noexcept {
            return impl.rend();
        }
    
        const_iterator cend() const noexcept {
            return impl.crend();
        }
    
    
        
        const_iterator rbegin() const noexcept {
            return impl.begin();
        }
    
        iterator rbegin() noexcept {
            return impl.begin();
        }
    
        const_iterator crbegin() const noexcept {
            return impl.cbegin();
        }
    
        const_iterator rend() const noexcept {
            return impl.end();
        }
    
        iterator rend() noexcept {
            return impl.end();
        }
    
        const_iterator crend() const noexcept {
            return impl.cend();
        }
    
    };
    
    template <class Container>
    constexpr ReversedIterable<Container> reversed(Container& container) noexcept {
        return ReversedIterable(container);
    }
    
    template <class Container>
    class ConstReversedIterable {
    
    private:
        
        const Container& impl;
    
    public:
        
        explicit constexpr ConstReversedIterable(const Container& impl) noexcept : impl(impl) {}
        
        using const_iterator = typename Container::const_reverse_iterator;
        using const_reverse_iterator = typename Container::const_iterator;
        
        const_iterator begin() const noexcept {
            return impl.rbegin();
        }
        
        const_iterator cbegin() const noexcept {
            return impl.crbegin();
        }
        
        const_iterator end() const noexcept {
            return impl.rend();
        }
        
        const_iterator cend() const noexcept {
            return impl.crend();
        }
        
        
        
        const_iterator rbegin() const noexcept {
            return impl.begin();
        }
        
        const_iterator crbegin() const noexcept {
            return impl.cbegin();
        }
        
        const_iterator rend() const noexcept {
            return impl.end();
        }
        
        const_iterator crend() const noexcept {
            return impl.cend();
        }
        
    };
    
    template <class Container>
    constexpr ConstReversedIterable<Container> reversed(const Container& container) noexcept {
        return ConstReversedIterable(container);
    }
    
}
