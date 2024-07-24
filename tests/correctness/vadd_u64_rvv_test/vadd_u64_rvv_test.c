// Copyright 2024 10xEngineers

#include "../../../common/print.h"

#ifdef ARM_NEON
    #include <arm_neon.h>
#else
#ifdef RISCV_VECTOR
    #include "../../../common/rhal_base.h"
#endif
#endif

// Function to run test cases with a given func_ptr
void run_test_cases(void (*func_ptr)(uint64_t*, uint64_t*, int, uint64_t*)) {
    uint64_t test_cases[][1] = {
        {6},                                   // Regular positive number
        {0},                                   // All zeros
        {18446744073709551615ULL},             // Maximum uint64_t value
        {5000000000000000000ULL},              // Large positive number
        {1},                                   // All ones
    };

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (int i = 0; i < num_tests; i++) {
        uint64_t *a = test_cases[i];
        uint64_t b[1] = {1};
        uint64_t result[1];

        func_ptr(a, b, 1, result);
        print_results(result, 1, "uint64_t");
    }
}

#ifdef ARM_NEON
// ARM Neon-specific implementation
void vadd_u64_neon(uint64_t *a, uint64_t *b, int size, uint64_t *result) {
    uint64x1_t x = vld1_u64(a);
    uint64x1_t y = vld1_u64(b);
    uint64x1_t z = vadd_u64(x, y);
    vst1_u64(result, z);
}
// Function to run tests using ARM Neon instructions/intrinsics
void run_tests_neon() {
    run_test_cases(vadd_u64_neon);
}
#endif

#ifdef RISCV_VECTOR
// RISC-V Vector-specific implementation
void vadd_u64_rvvector(uint64_t *a, uint64_t *b, int size, uint64_t *result) {
    uint64x1_t x = __riscv_vle64_v_u64m1(a, size);
    uint64x1_t y = __riscv_vle64_v_u64m1(b, size);
    uint64x1_t z = vadd_u64_rvv(x, y);
    __riscv_vse64_v_u64m1(result, z, size);
}
// Function to run tests using RISC-V Vector instructions/intrinsics
void run_tests_rvv() {
    run_test_cases(vadd_u64_rvvector);
}
#endif

int main() {
    #ifdef RISCV_VECTOR
        run_tests_rvv();
    #endif
    #ifdef ARM_NEON
        run_tests_neon();
    #endif
    return 0;
}
