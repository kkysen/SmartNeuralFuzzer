//
// Created by Khyber on 7/18/2019.
//

#pragma once

#include "src/share/common/math.h"

#include "llvm/IR/Instructions.h"

namespace llvm {
    
    // this could easily get messed up in future updates if internals get changed
    
    class CallBaseHack : CallBase {
    
    private:
        
        // unnamed padded data for extra data in CallBase child class
        // this'll let me reinterpret_cast to any of them
        static constexpr auto maxSubClassSize = math::maxSize<CallInst, InvokeInst, CallBrInst>();
        using SubClassData = std::array<u8, maxSubClassSize - sizeof(CallBase)>;
        SubClassData subClassData;
        
        static SubClassData getSubClassData(const CallBase& inst);
        
        CallBaseHack(const CallBase& inst, ArrayRef<Value*> args);
        
        static CallBase& cloneWithNewArgsImpl(const CallBase& inst, ArrayRef<Value*> args);
    
    public:
        
        template <typename CallInstType>
        static CallInstType& cloneWithNewArgs(const CallInstType& inst, ArrayRef<Value*> args) {
            return reinterpret_cast<CallInstType&>(cloneWithNewArgsImpl(inst, args));
        }
        
    };
    
    template <typename CallInstType>
    CallInstType& cloneWithNewArgs(CallInstType& inst, ArrayRef<Value*> args) {
        return CallBaseHack::cloneWithNewArgs(inst, args);
    }
    
}
