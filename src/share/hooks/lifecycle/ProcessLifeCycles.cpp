//
// Created by Khyber on 6/3/2019.
//

#include "src/share/hooks/lifecycle/ProcessLifeCycles.h"

#include "src/share/hooks/lifecycle/ThreadLifeCycles.h"
#include "src/share/hooks/libc/syscall/gettid.h"
#include "src/share/hooks/libc/syscall/sigqueueinfo.h"
#include "src/share/aio/signal/Info.h"
#include "src/share/common/odrUse.h"

#include <random>

#include <unistd.h>
#include <src/share/hooks/lifecycle/signaling/Sender.h>

namespace hooks::lifecycle {
    
    ProcessLifeCycles::Own ProcessLifeCycles::add() {
        return tids.add(gettid());
    }
    
    ProcessLifeCycles ProcessLifeCycles::instance;
    
    thread_local auto ProcessLifeCycles::own = get().add();
    
    void ProcessLifeCycles::onThreadCreation() noexcept {
        thread::onCreation();
        odrUse(own);
    }
    
    void ProcessLifeCycles::onThreadDestruction() noexcept {
        thread::onDestruction();
        delete& own;
    }
    
    void ProcessLifeCycles::reconstruct() noexcept {
        tids.clear();
        own.operator=(std::move(add()));
//            own = add();
    }
    
    void ProcessLifeCycles::destruct() const noexcept {
        signaling::Sender send;
        tids.forEach([&send](const pid_t tid) {
            send(tid);
        });
        tids.onNoThreadsLeft().wait();
        // now we've cleaned up all the thread_local ThreadLifeCycles
    }
    
    void ProcessLifeCycles::onProcessCreation() noexcept {
        get().reconstruct();
    }
    
    void ProcessLifeCycles::onProcessDestruction() noexcept {
        get().destruct();
    }
    
}
