// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise halving addition of two 32-bit unsigned integer vectors.
 * 
 * This function performs an element-wise addition of two 32-bit unsigned integer vectors (`a` and `b`),
 * each containing two elements, and then halves the result by shifting the sum of each pair of elements 
 * to the right by 1 bit. It utilizes the RISC-V Vector Extension to carry out the operation, making it 
 * analogous to the ARM Neon function `vhadd_u32`. The result is a new vector where each element is 
 * the halved sum of the corresponding elements in the input vectors, with the result stored as 
 * 32-bit unsigned integers.
 * 
 * @param a The first input vector of type uint32x2_t containing 32-bit unsigned integers.
 * @param b The second input vector of type uint32x2_t containing 32-bit unsigned integers.
 * @return uint32x2_t The result of the halving addition, returned as an 32-bit unsigned integer vector.
 */
uint32x2_t vhadd_u32_rvv(uint32x2_t a, uint32x2_t b) {
    return __riscv_vnsrl_wx_u32m1( __riscv_vwaddu_vv_u64m2(a, b, VLEN_2), 1, VLEN_2);
}