//
// Created by Khyber on 2/14/2019.
//

#pragma once

#include "src/share/common/numbers.h"
#include "src/share/llvm/Types.h"
#include "src/share/llvm/Constants.h"
#include "src/share/llvm/IRBuilderExt.h"
#include "src/share/llvm/alignment.h"
#include "src/share/llvm/AllocaArgs.h"
#include "src/share/llvm/LoadStore.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"

namespace llvm {
    
    class LLVMArray : public IRBuilderExt {
    
    public:
        
        const Type* type;
        const Value* ptr;
        const Value* size;
        const u32 alignment;
        
        const bool hasConstSize;
    
    public:
        
        LLVMArray(IRBuilder<>& builder, const Type* type, const Value* ptr, const Value* size,
                  u32 alignment = alignment::unAligned) noexcept :
                IRBuilderExt(builder),
                type(type),
                ptr(ptr),
                size(size),
                alignment(alignment),
                hasConstSize(isa<ConstantInt>(size)) {}
        
        LLVMArray withBuilder(IRBuilder<>& builder) const {
            return LLVMArray(builder, type, ptr, size, alignment);
        }
        
        template <typename T>
        LLVMArray(IRBuilder<>& builder, const Value* ptr, const Value* size,
                  u32 alignment = alignment::unAligned) noexcept :
                LLVMArray(builder, types().get<T>(), ptr, size, alignment) {}
        
        LLVMArray(IRBuilder<>& builder, AllocaInst* allocaInst) noexcept :
                LLVMArray(builder, allocaInst->getAllocatedType(),
                          allocaInst, allocaInst->getArraySize(), allocaInst->getAlignment()) {}
        
        LLVMArray(AllocaArgs args) noexcept
                : LLVMArray(args.builder, args()) {}
        
        constexpr bool isAligned() const noexcept {
            return alignment == alignment::unAligned;
        }
        
        u64 constSize() const {
            return cast<ConstantInt>(size)->getZExtValue();
        }
        
        constexpr const Value* front() const noexcept {
            return ptr;
        }
        
        constexpr const Value* back() const noexcept {
            return *this + size;
        }
        
        constexpr const Value* operator+(const Value* index) const {
            if (hasConstSize) {
                if (const auto constIndex = dyn_cast<ConstantInt>(index)) {
                    return *this + constIndex;
                }
            }
            return builder.CreateGEP(mut(type), mut(ptr), mut(index));
        }
        
        constexpr const Value* operator+(const ConstantInt* index) const {
            if (hasConstSize) {
                if (index->getZExtValue() < constSize()) {
                    return builder.CreateInBoundsGEP(mut(type), mut(ptr), mut(index));
                }
            }
            return builder.CreateInBoundsGEP(mut(type), mut(ptr), mut(index));
        }
        
        constexpr const Value* operator+(u64 index) const {
            return builder.CreateConstGEP1_64(mut(type), mut(ptr), index);
        }
        
        constexpr const Value* operator+(u32 index) const {
            return builder.CreateConstGEP1_32(mut(type), mut(ptr), index);
        }
        
        constexpr LoadStore operator[](const Value* index) const {
            return LoadStore(builder, *this + index, alignment);
        }
        
        constexpr LoadStore operator[](const ConstantInt* index) const {
            return LoadStore(builder, *this + index, alignment);
        }
        
        constexpr LoadStore operator[](u64 index) const {
            return LoadStore(builder, *this + index, alignment);
        }
        
        constexpr LoadStore operator[](u32 index) const {
            return LoadStore(builder, *this + index, alignment);
        }
        
        constexpr CallInst* memset(const Value* value) const {
            return builder.CreateMemSet(mut(ptr), mut(value), mut(size), alignment);
        }
        
        constexpr CallInst* memset(u8 value = 0) const {
            return memset(constants().getInt<u8>(value));
        }
        
        constexpr CallInst* memClear() const {
            return memset();
        }
        
        LLVMArray bitCast(const Type* type) const {
            const auto castedPtr = builder.CreateBitCast(mut(ptr), mut(type));
            return LLVMArray(builder, type, castedPtr, size, alignment);
        }
        
        template <typename T>
        LLVMArray bitCast() const {
            return bitCast(types().get<T>());
        }
        
    };
    
}
