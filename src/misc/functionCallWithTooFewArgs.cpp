//
// Created by Khyber on 7/24/2019.
//

#include <random>
#include <iostream>

using RR = int;

using R = void;
using F0 = R();
using F1 = R(int);
using F2 = R(int, int);
using F3 = R(int, int, int);

extern "C"
RR p(int x) {
    std::cout << "p = " << x << std::endl;
    return x;
}

extern "C"
RR f0() {
    return p(-1);
}

extern "C"
RR f1(int a) {
    return p(a);
}

extern "C"
RR f2(int a, int b) {
    return p(a + b);
}

extern "C"
RR f3(int a, int b, int c) {
    return p(a + b + c);
}

extern "C"
void* funcs[] = {
        reinterpret_cast<void*>(f0),
        reinterpret_cast<void*>(f1),
        reinterpret_cast<void*>(f2),
        reinterpret_cast<void*>(f3),
};

extern "C"
void g0(int i) {
    const auto f = reinterpret_cast<F0*>(funcs[i]);
    const auto x = (f(), 0);
    std::cout << "x0 = " << x << std::endl;
}

extern "C"
void g1(int i) {
    const auto f = reinterpret_cast<F1*>(funcs[i]);
    const auto x = (f(100), 1);
    std::cout << "x1 = " << x << std::endl;
}

extern "C"
void g2(int i) {
    const auto f = reinterpret_cast<F2*>(funcs[i]);
    const auto x = (f(-1, -2), 2);
    std::cout << "x2 = " << x << std::endl;
}

extern "C"
void g3(int i) {
    const auto f = reinterpret_cast<F3*>(funcs[i]);
    const auto x = (f(1, 2, 3), 3);
    std::cout << "x3 = " << x << std::endl;
}

/**
 * Test if I can call a function with the wrong number of arguments and different return type.
 *
 * Result:
 *      If I call with too many args, everything seems fine.
 *      If I call with too few args, garbage values are in the args instead,
 *          but there's no segfault and if the args aren't actually used this should be fine.
 *      If I call with a larger return type, garbage values are used for the rest of the type.
 *      But if I call with a void return type (when it's not void),
 *          things sometimes get messed up (but nothing crashes).
 */
int main(int argc, char** argv) {
    std::default_random_engine generator {std::random_device()()};
    std::uniform_int_distribution<int> distribution(0, (sizeof(funcs) / sizeof(*funcs)) - 1);
    
    const auto i = argc < 2
            ? distribution(generator)
            : std::strtoull(argv[1], nullptr, 10) % (sizeof(funcs) / sizeof(*funcs));
    std::cout << "i = " << i << std::endl;
    
    g0(i);
    g1(i);
    g2(i);
    g3(i);
    
    return 0;
}
