//
// Created by Khyber on 5/26/2019.
//

#pragma once

#define RAII_API() \
    api(reconstruct)() noexcept; \
    api(flushData)() noexcept; \
    api(destruct)() noexcept; \
