//
// Created by Khyber on 7/8/2019.
//

#pragma once

#include <string_view>

namespace io {
    
    template <class Reader>
    class ReaderWrapper {

    public:
        
        using Data = typename Reader::Data;
        
    protected:
        
        Reader reader;
        
    public:
    
        explicit constexpr ReaderWrapper(Data&& data) noexcept : reader(std::move(data)) {}
    
        constexpr bool done() const noexcept {
            return reader.done();
        }
    
        constexpr bool hasNext() const noexcept {
            return reader.hasNext();
        }
    
        constexpr bool hasError() const noexcept {
            return reader.hasError();
        }
    
        constexpr std::string_view error() const noexcept {
            return reader.error();
        }
        
    };
    
}
