// Copyright 2024 10xEngineers

#include "rhal_base.h"

/**
 * @brief Performs an element-wise unsigned saturating addition of two 128-bit vectors of 32-bit unsigned integers.
 * 
 * This function performs an element-wise addition of two 32-bit unsigned integer vectors (`a` and `b`), 
 * each containing four elements. If the result of the addition exceeds the range of an 32-bit unsigned integer 
 * (0 to 4294967295), the result is saturated to the nearest boundary (either 0 or 4294967295). It utilizes the RISC-V 
 * Vector Extension to carry out the operation, making it analogous to the ARM Neon function `vqaddq_u32`. 
 * The result is a new vector where each element is the saturating sum of the corresponding elements in the input vectors.
 * 
 * @param a The first input vector of type uint32x4_t containing 32-bit unsigned integers.
 * @param b The second input vector of type uint32x4_t containing 32-bit unsigned integers.
 * @return uint32x4_t The result of the element-wise saturating addition, returned as an 32-bit unsigned integer vector.
 */
uint32x4_t vqaddq_u32_rvv(uint32x4_t a, uint32x4_t b) {
    return __riscv_vsaddu_vv_u32m1(a, b, VLEN_4);
}