//
// Created by Khyber on 2/4/2019.
//

#include "main.h"

#include <iostream>
#include <vector>

#include "Tracer.h"

void g() {
    printf("g: return: %p, frame: %p, %p\n", __builtin_return_address(0), __builtin_frame_address(0), __builtin_frame_address(1));
}

void f() {
    g();
    printf("f\n");
    g();
    printf("parent frame: %p\n", __builtin_frame_address(1));
}

int main(int argc, char** argv) {
    std::cout << "\t\tstart main()" << std::endl;
//    Tracer tracer;
//    std::vector<u32> v;
//    v.reserve(100);
//    tracer.init(v.begin().base(), v.end().base());
//    tracer.mark(&v[5]);
//    std::cout << "Hello, World" << std::endl;
    f();
    
    printf("main() address: %p\n", &main);
    printf("main() return: %p\n", __builtin_return_address(0));
    printf("main() frame: %p\n", __builtin_frame_address(0));
    
    for (u64 i = 10; i >= argc; i--) {
        printf("i = %lu\n", i);
    }
    for (u64 i = 10; i > argc; i--) {
        printf("i = %lu\n", i);
    }
    
    return 0;
}