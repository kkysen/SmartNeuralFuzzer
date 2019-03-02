//
// Created by Khyber on 2/17/2019.
//

#pragma once

#include "IRBuilderExt.h"
#include "alignment.h"

namespace llvm {
    
    class LoadStore : public IRBuilderExt {
    
    public:
        
        const Value* ptr;
        const u32 alignment;
        
        constexpr LoadStore(IRBuilder<>& builder, const Value* ptr, u32 alignment = alignment::unAligned) noexcept
                : IRBuilderExt(builder), ptr(ptr), alignment(alignment) {}
        
        constexpr LoadInst* load() const {
            if (alignment != alignment::unAligned) {
                return builder.CreateAlignedLoad(mut(ptr), alignment);
            } else {
                return builder.CreateLoad(mut(ptr));
            }
        }
        
        constexpr StoreInst* store(const Value* value) const {
            if (alignment != alignment::unAligned) {
                return builder.CreateAlignedStore(mut(value), mut(ptr), alignment);
            } else {
                return builder.CreateStore(mut(value), mut(ptr));
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
