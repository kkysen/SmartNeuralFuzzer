//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hook/lifecycle/ProcessLifeCycles.h"

#include "src/share/hook/lifecycle/ThreadLifeCycles.h"
#include "src/share/hook/lifecycle/signaling/Sender.h"
#include "src/share/hook/libc/syscall/gettid.h"
#include "src/share/common/odrUse.h"

namespace hook::lifecycle {
    
    ProcessLifeCycles::Own ProcessLifeCycles::add() {
        return tids.add(gettid());
    }
    
    ProcessLifeCycles ProcessLifeCycles::instance;
    
    thread_local auto ProcessLifeCycles::own = get().add();
    
    void ProcessLifeCycles::onThreadConstruction() noexcept {
        thread::construct();
        odrUse(own);
    }
    
    void ProcessLifeCycles::onThreadDestruction() noexcept {
        thread::destruct();
        delete& own;
    }
    
    void ProcessLifeCycles::reconstruct() {
        tids.clear();
        own = add();
    }
    
    void ProcessLifeCycles::destruct() const noexcept {
        signaling::Sender send;
        tids.forEach([&send](const pid_t tid) {
            send(tid);
        });
        tids.onNoThreadsLeft().wait();
        // now we've cleaned up all the thread_local ThreadLifeCycles
    }
    
    void ProcessLifeCycles::onProcessReconstruction() {
        get().reconstruct();
        thread::reconstruct();
    }
    
    void ProcessLifeCycles::onProcessDestruction() noexcept {
        get().destruct();
    }
    
}
