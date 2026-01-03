//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_MANTISSA_H
#define LIBMA_MANTISSA_H

/* src/internal/mantissa.h */
#pragma once

#include "fp_classify.h"
#include "normalize.h"

/* Extract an integer mantissa and an unbiased exponent.
   These are useful for log/pow/exp range reduction and for building
   correctly-rounded kernels.

   Conventions:
   - For normal numbers:
       float:  x = (m / 2^23) * 2^e, with m in [2^23, 2^24)
       double: x = (m / 2^52) * 2^e, with m in [2^52, 2^53)
     i.e. m includes the implicit leading 1.
   - For subnormals:
       m is normalized to the same range by shifting, and e is adjusted.
   - For zero/Inf/NaN:
       return 0 and set *e = 0 (caller should classify first).
   - Sign is NOT included in m; caller handles sign separately.
*/

/* ---------- float ---------- */
/**
 * Computes the 23-bit mantissa (with an implicit leading 1 for normalized values)
 * of the given floating-point number. Also determines the exponent value.
 *
 * @param x The input floating-point number for which the mantissa is to be computed.
 * @param e Pointer to an integer where the computed exponent will be stored.
 *          The exponent is calculated relative to the floating-point bias.
 * @return The 23-bit mantissa of the floating-point number. Returns 0 for
 *         values representing zero or special cases like infinity and NaN.
 */
LIBMA_ALWAYS_INLINE_STATIC uint32_t ker_flt_mantissa_u32(const float x, int* e) {
    const uint32_t u = ker_flt_to_u32(x);
    const uint32_t frac = ker_flt_frac_u32(u);
    const int exp = ker_flt_exp_u32(u);

    if(exp == 0) {
        if(frac == 0) {
            *e = 0;
            return 0;
        } /* zero */
        /* subnormal: normalize so leading 1 lands at bit 23 */
        const int lead = 31 - ker_libma_clz32(frac); /* 0..22 */
        const int shift = 23 - lead; /* 1..23 */
        uint32_t m = frac << shift; /* now has 1 at bit 23 */
        *e = 1 - FLT_EXP_BIAS - shift;
        return m; /* m in [2^23, 2^24) */
    }

    if(exp == 0xFF) {
        *e = 0;
        return 0;
    } /* Inf/NaN */

    *e = exp - FLT_EXP_BIAS;
    return (1u << 23) | frac; /* m in [2^23, 2^24) */
}

/* If you want the signed mantissa (two's complement) */
/**
 * Computes the signed 23-bit mantissa (with an implicit leading 1 for normalized values)
 * of the given floating-point number. Also determines the exponent value.
 *
 * @param x The input floating-point number for which the signed mantissa is to be computed.
 * @param e Pointer to an integer where the computed exponent will be stored.
 *          The exponent is calculated relative to the floating-point bias.
 * @return The signed 23-bit mantissa of the floating-point number. Returns 0 for
 *         values representing zero or special cases like infinity and NaN.
 */
LIBMA_ALWAYS_INLINE_STATIC int32_t ker_flt_mantissa_i32(const float x, int* e) {
    const uint32_t u = ker_flt_to_u32(x);
    const int sign = ker_flt_sign_u32(u);
    const uint32_t m = ker_flt_mantissa_u32(x, e);
    return sign ? -(int32_t)m : (int32_t)m;
}

/* ---------- double ---------- */
/**
 * Computes the 52-bit mantissa (with an implicit leading 1 for normalized values)
 * of the given double-precision floating-point number. Also determines the exponent value.
 *
 * @param x The input double-precision floating-point number for which the mantissa is to be computed.
 * @param e Pointer to an integer where the computed exponent will be stored.
 *          The exponent is calculated relative to the double-precision floating-point bias.
 * @return The 52-bit mantissa of the floating-point number. Returns 0 for
 *         values representing zero, subnormal numbers, or special cases like infinity and NaN.
 */
LIBMA_ALWAYS_INLINE_STATIC uint64_t ker_dbl_mantissa_u64(const double x, int* e) {
    const uint64_t u = ker_dbl_to_u64(x);
    const uint64_t frac = ker_dbl_frac_u64(u);
    const int exp = ker_dbl_exp_u64(u);

    if(exp == 0) {
        if(frac == 0) {
            *e = 0;
            return 0;
        } /* zero */
        /* subnormal: normalize so leading 1 lands at bit 52 */
        const int lead = 63 - ker_libma_clz64(frac); /* 0..51 */
        const int shift = 52 - lead; /* 1..52 */
        const uint64_t m = frac << shift; /* now has 1 at bit 52 */
        *e = 1 - DBL_EXP_BIAS - shift;
        return m; /* m in [2^52, 2^53) */
    }

    if(exp == 0x7FF) {
        *e = 0;
        return 0;
    } /* Inf/NaN */

    *e = exp - DBL_EXP_BIAS;
    return (1ULL << 52) | frac; /* m in [2^52, 2^53) */
}

/**
 * Computes the signed 53-bit mantissa (with an implicit leading 1 for normalized values)
 * of the given floating-point number and determines its associated exponent value.
 *
 * @param x The input floating-point number for which the mantissa is to be computed.
 * @param e Pointer to an integer where the computed exponent will be stored.
 *          The exponent is calculated relative to the double-precision floating-point bias.
 * @return The signed 53-bit mantissa of the floating-point number. Returns 0 for
 *         values representing zero or special cases like infinity and NaN.
 */
LIBMA_ALWAYS_INLINE_STATIC int64_t ker_dbl_mantissa_i64(const double x, int* e) {
    const uint64_t u = ker_dbl_to_u64(x);
    const int sign = ker_dbl_sign_u64(u);
    const uint64_t m = ker_dbl_mantissa_u64(x, e);
    return sign ? -(int64_t)m : (int64_t)m;
}


#endif //LIBMA_MANTISSA_H
