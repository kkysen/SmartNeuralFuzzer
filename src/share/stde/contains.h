//
// Created by Khyber on 4/11/2019.
//

#pragma once

#include <algorithm>
#include <string_view>

namespace stde {
    
    using namespace std;
    
    template <class InputIt, class T>
    bool contains(InputIt first, InputIt last, const T& value) {
        return find(first, last, value) != last;
    }
    
    template <class ExecutionPolicy, class ForwardIt, class T>
    bool contains(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, const T& value) {
        return find(policy, first, last, value) != last;
    }
    
    template <class InputIt, class UnaryPredicate>
    bool contains_if(InputIt first, InputIt last, UnaryPredicate p) {
        return find_if(first, last, p) != last;
    }
    
    template <class ExecutionPolicy, class ForwardIt, class UnaryPredicate>
    bool contains_if(ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryPredicate p) {
        return find_if(policy, first, last, p) != last;
    }
    
    
    
    template <class CharT, class Traits = std::char_traits<CharT>>
    class Containing {
    
    public:
        
        using StringView = std::basic_string_view<CharT, Traits>;
    
    private:
        
        const StringView& contains;
    
    public:
        
        explicit constexpr Containing(const StringView& contains) noexcept : contains(contains) {}
        
        constexpr bool operator()(const StringView& string) const noexcept {
            return string.find(contains) != StringView::npos;
        }
        
        template <class Allocator = std::allocator<CharT>>
        bool operator()(const std::basic_string<CharT, Traits, Allocator> string) const noexcept {
            return string.find(contains) != std::basic_string<CharT, Traits, Allocator>::npos;
        }
        
    };
    
    template <class CharT, class Traits = std::char_traits<CharT>>
    constexpr Containing<CharT, Traits> containing(const basic_string_view<CharT, Traits>& contains) noexcept {
        return Containing(contains);
    }
    
}
