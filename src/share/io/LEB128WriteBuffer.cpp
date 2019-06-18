//
// Created by Khyber on 6/18/2019.
//

#include "src/share/io/LEB128WriteBuffer.h"

namespace io {
    
    // LEB128 algorithms copied from https://llvm.org/doxygen/LEB128_8h_source.html
    
    u8 LEB128WriteBuffer::on(u64 value, u8 padTo) noexcept {
        u8 count = 0;
        do {
            u8 byte = value & 0x7Fu;
            value >>= 7u;
            count++;
            if (value != 0 || count < padTo)
                byte |= 0x80u; // Mark this byte to show that more bytes will follow.
            buffer << byte;
        } while (value != 0);
    
        // Pad with 0x80 and emit a null byte at the end.
        if (count < padTo) {
            for (; count < padTo - 1; ++count)
                buffer << '\x80';
            buffer << '\x00';
            count++;
        }
        return count;
    }
    
    u8 LEB128WriteBuffer::on(i64 value, u8 padTo) noexcept {
        bool more;
        u8 count = 0;
        do {
            u8 byte = value & 0x7F; // NOLINT(hicpp-signed-bitwise)
            // NOTE: this assumes that this signed shift is an arithmetic right shift.
            value >>= 7u; // NOLINT(hicpp-signed-bitwise)
            more = !((((value == 0 ) && ((byte & 0x40u) == 0)) ||
                      ((value == -1) && ((byte & 0x40u) != 0))));
            count++;
            if (more || count < padTo)
                byte |= 0x80u; // Mark this byte to show that more bytes will follow.
            buffer << byte;
        } while (more);
    
        // Pad with 0x80 and emit a terminating byte at the end.
        if (count < padTo) {
            u8 padValue = value < 0 ? 0x7Fu : 0x00u;
            for (; count < padTo - 1; ++count)
                buffer << (padValue | 0x80u);
            buffer << padValue;
            count++;
        }
        return count;
    }
    
}
