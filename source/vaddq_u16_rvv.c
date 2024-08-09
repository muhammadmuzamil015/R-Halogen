// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Adds two 128-bit vectors of 16-bit unsigned integers element-wise.
 * 
 * This function performs an element-wise addition of two 16-bit unsigned integer vectors (`a` and `b`), 
 * each containing eight elements. It utilizes the RISC-V Vector Extension to carry out the operation, 
 * making it analogous to the ARM Neon function `vaddq_u16`. The result is a new vector where each element 
 * is the sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint16x8_t containing 16-bit unsigned integers.
 * @param b The second input vector of type uint16x8_t containing 16-bit unsigned integers.
 * @return uint16x8_t The result of the element-wise addition, returned as an 16-bit unsigned integer vector.
 */
uint16x8_t vaddq_u16_rvv(uint16x8_t a, uint16x8_t b) {
    return __riscv_vadd_vv_u16m1(a, b, VLEN_8);
}
