//
// Created by Khyber on 4/6/2019.
//

#include "src/share/aio/IdempotentWriter.h"

namespace aio {
    
    void IdempotentWriter::write() const noexcept {
        // no need to make multiple aio_write()s before the last one finished
        // when the aio_write() actually writes, it'll read the already updated data in buffer/
        // therefore, I only need to call aio_write() when the cb is idle
        if (cb.idle()) {
            cb.write();
        }
    }
    
    IdempotentWriter::~IdempotentWriter() {
        write();
        close(cb.fd());
    }
    
    
}
