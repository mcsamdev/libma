//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_NORMALIZE_H
#define LIBMA_NORMALIZE_H

#include "fp_classify.h"

/* Normalize:
   x = m * 2^e, with m in [1,2) for finite nonzero x.
   Caller should handle 0/Inf/NaN.

   This uses clz-based normalization on GCC/Clang (x86-64, AArch64),
   with a portable loop fallback otherwise.
*/
/**
 * Counts the number of leading zero bits in a 32-bit unsigned integer.
 *
 * This function determines the number of contiguous zero bits starting from the most significant
 * bit of the given 32-bit integer. The input value must be non-zero in order to avoid undefined behavior.
 *
 * @param x The input 32-bit unsigned integer. The caller must guarantee that x is not zero.
 * @return The number of leading zero bits in the input value.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_libma_clz32(uint32_t x) {
#if (LIBMA_GCC || LIBMA_CLANG)
    /* __builtin_clz(0) is UB; caller guarantees x != 0 */
    return __builtin_clz(x);
#else
    int n = 0;
    while((x & 0x80000000u) == 0) {
        x <<= 1;
        n++;
    }
    return n;
#endif
}

/**
 * Counts the number of leading zero bits in a 64-bit unsigned integer.
 *
 * This function determines the number of contiguous zero bits starting from the most significant
 * bit of the given 64-bit integer. The input value must be non-zero in order to avoid undefined behavior.
 *
 * @param x The input 64-bit unsigned integer. The caller must guarantee that x is not zero.
 * @return The number of leading zero bits in the input value.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_libma_clz64(uint64_t x) {
#if (LIBMA_GCC || LIBMA_CLANG)
    return __builtin_clzll(x);
#else
    int n = 0;
    while((x & 0x8000000000000000ULL) == 0) {
        x <<= 1;
        n++;
    }
    return n;
#endif
}

/* float */
/**
 * Normalizes a floating-point number such that it has a leading 1 in its fraction
 * (for normalized numbers) or bit 23 forced to 1 (for subnormal numbers).
 *
 * @param x The input floating-point number to be normalized. Must not be zero.
 * @param e Pointer to an integer that will receive the unbiased exponent of the normalized value.
 *          For normalized inputs, it is calculated as the input's exponent minus the bias (127).
 *          For subnormal inputs, it is derived based on the leading bit's position after normalization.
 * @return The normalized floating-point number, with its fraction adjusted and exponent set to the bias (127).
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_normalize(const float x, int* e) {
    uint32_t u = ker_flt_to_u32(x);
    const int exp = ker_flt_exp_u32(u);
    uint32_t frac = ker_flt_frac_u32(u);

    if(exp == 0) {
        /* subnormal (caller should have excluded zero) */
        /* We want to shift frac so that bit 23 becomes 1. */
        /* frac is in bits [22:0], so its top possible bit is 22. */
        /* lead index = 31 - clz(frac). We need shift = 23 - lead. */
        const int lead = 31 - ker_libma_clz32(frac);
        const int shift = 23 - lead;

        frac <<= shift; /* now has the 1 at bit 23 */
        frac &= FLT_FRAC_MASK; /* drop the implicit 1 */
        *e = 1 - FLT_EXP_BIAS - shift;

        const uint32_t norm = ((uint32_t)FLT_EXP_BIAS << 23) | frac | (u & FLT_SIGN_MASK);
        return ker_u32_to_flt(norm);
    }

    *e = exp - FLT_EXP_BIAS;
    u = (u & (FLT_SIGN_MASK | FLT_FRAC_MASK)) | ((uint32_t)FLT_EXP_BIAS << 23);
    return ker_u32_to_flt(u);
}

/* double */
/**
 * Normalizes a double-precision floating-point number such that it has a leading 1 in its fraction
 * (for normalized numbers) or bit 52 forced to 1 (for subnormal numbers).
 *
 * @param x The input double-precision floating-point number to normalize. Must not be zero.
 * @param e Pointer to an integer that will receive the unbiased exponent of the normalized value.
 *          If the input is subnormal, the exponent is derived based on the leading bit's position
 *          after normalization. If the input is normalized, the exponent is calculated by subtracting
 *          the bias (1023) from its actual exponent.
 * @return The normalized double-precision floating-point number, with its fraction adjusted and exponent
 *         set to the bias (1023).
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_normalize(const double x, int* e) {
    uint64_t u = ker_dbl_to_u64(x);
    const int exp = ker_dbl_exp_u64(u);
    uint64_t frac = ker_dbl_frac_u64(u);

    if(exp == 0) {
        /* subnormal (caller should have excluded zero) */
        /* Need to shift frac so bit 52 becomes 1.
           frac is in bits [51:0], top possible bit 51. */
        const int lead = 63 - ker_libma_clz64(frac);
        const int shift = 52 - lead;

        frac <<= shift; /* now has the 1 at bit 52 */
        frac &= DBL_FRAC_MASK; /* drop the implicit 1 */
        *e = 1 - DBL_EXP_BIAS - shift;

        const uint64_t norm = ((uint64_t)DBL_EXP_BIAS << 52) | frac | (u & DBL_SIGN_MASK);
        return ker_u64_to_dbl(norm);
    }

    *e = exp - DBL_EXP_BIAS;
    u = (u & (DBL_SIGN_MASK | DBL_FRAC_MASK)) | ((uint64_t)DBL_EXP_BIAS << 52);
    return ker_u64_to_dbl(u);
}

#endif //LIBMA_NORMALIZE_H
