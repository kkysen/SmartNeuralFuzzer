//
// Created by Khyber on 2/4/2019.
//

#include "hooks.h"

#include "Tracer.h"

#include "sanitizer/coverage_interface.h"

static bool global1 = true;
static bool global2 = false;
static bool global3 = false;

class C {

public:

    bool initialized = false;

    C() {
        initialized = true;
        global3 = true;
    }

} globalC;

void check() {
    printf("true = %s, false = %s, true = %s, true = %s\n",
           global1 ? "true" : "false",
           global2 ? "true" : "false",
           global3 ? "true" : "false",
           globalC.initialized ? "true" : "false"
    );
}

void __sanitizer_cov_trace_pc_guard_init(u32* start, u32* stop) {
    check();
    printf("%p..%p\n", start, stop);
    static u32 n = 0;
    if (start == stop || *start) {
        return; // only initialize once
    }
    for (u32* guard = start; guard < stop; guard++) {
        *guard = ++n; // guard should start from 1 (non 0)
    }
}

void __sanitizer_cov_trace_pc_guard(u32* guard) {
    if (!*guard) {
        return; // duplicate guard check
    }
//    check();
    printf("true = %s, false = %s, true = %s, true = %s\n",
           global1 ? "true" : "false",
           global2 ? "true" : "false",
           global3 ? "true" : "false",
           globalC.initialized ? "true" : "false"
    );
//    printf("guard: %p\n", guard);

    void *PC = __builtin_return_address(0);
    char PcDescr[1024];
    // This function is a part of the sanitizer run-time.
    // To use it, link with AddressSanitizer or other sanitizer.
    __sanitizer_symbolize_pc(PC, "%p %F %L", PcDescr, sizeof(PcDescr));
    printf("guard: %p %x PC %s\n", guard, *guard, PcDescr);
//    printf("%p ", PC);
    fflush(stdout);
    char cmd[1024] = {};
    sprintf(cmd, "addr2line -e DifferentiableFuzzer -p -f -C %p", PC);
    system(cmd);
    printf("\n");
    fflush(stdout);
//    printf("%p\n", &std::cout);
}

//static Tracer tracer;
//
//void __sanitizer_cov_trace_pc_guard_init(u32* start, u32* stop) {
//    printf("%p..%p\n", start, stop);
//    tracer.init(start, stop);
//}
//
//void __sanitizer_cov_trace_pc_guard(u32* guard) {
//    tracer.mark(guard);
//}

void __sanitizer_cov_trace_cmp1(u8 arg1, u8 arg2) {
    printf("cmp1(%u, %u)\n", arg1, arg2);
}

void __sanitizer_cov_trace_cmp2(u16 arg1, u16 arg2) {
    printf("cmp2(%u, %u)\n", arg1, arg2);
}

void __sanitizer_cov_trace_cmp4(u32 arg1, u32 arg2) {
//    check();
    printf("cmp4(%u, %u)\n", arg1, arg2);
}

void __sanitizer_cov_trace_cmp8(u64 arg1, u64 arg2) {
//    check();
    printf("cmp8(%lu, %lu)\n", arg1, arg2);
}