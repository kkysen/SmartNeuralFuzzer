//
// Created by Khyber on 7/27/2019.
//

#pragma once

namespace stde {

    template <class Container, class F>
    void forEachRemovable(Container&& container, F f) noexcept(noexcept(f(*container.begin()))) {
        for (auto it = container.begin(); it != container.end();) {
            f(*(it++));
        }
    }

}
