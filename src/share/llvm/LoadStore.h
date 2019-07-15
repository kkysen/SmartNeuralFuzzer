//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include "src/share/llvm/lib/alignment.h"
#include "src/share/llvm/IRBuilderExt.h"

namespace llvm {
    
    class LoadStore : public IRBuilderExt {
    
    public:
        
        const Value* ptr;
        const u32 alignment;
        
        constexpr LoadStore(IRBuilder<>& builder, const Value* ptr, u32 alignment = alignment::unAligned) noexcept
                : IRBuilderExt(builder), ptr(ptr), alignment(alignment) {}
        
        constexpr LoadInst* load() const {
            if (alignment != alignment::unAligned) {
                return irb.CreateAlignedLoad(mut(ptr), alignment);
            } else {
                return irb.CreateLoad(mut(ptr));
            }
        }
        
        constexpr StoreInst* store(const Value* value) const {
            if (alignment != alignment::unAligned) {
                return irb.CreateAlignedStore(mut(value), mut(ptr), alignment);
            } else {
                return irb.CreateStore(mut(value), mut(ptr));
            }
        }
        
        constexpr operator LoadInst*() const {
            return load();
        }
        
        constexpr LoadInst* operator*() const {
            return load();
        }
        
        constexpr StoreInst* operator=(const Value* value) const {
            return store(value);
        }
        
    };
    
}
