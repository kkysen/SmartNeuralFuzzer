//
// Created by Khyber on 6/5/2019.
//

#pragma once

#include "src/share/aio/signal/Signal.h"

#include <functional>

namespace aio::signal::handler {
    
    using HandlerFunc = std::function<void(const Signal& signal)>;
    
}
