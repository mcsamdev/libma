//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_FROM_MANTISSA_H
#define LIBMA_FROM_MANTISSA_H

#include "mantissa.h"
#include "scalbn.h"

/* Build a float/double from an integer mantissa (with implicit leading 1 at the top bit)
   and an unbiased exponent 'e' using the conventions from mantissa.h:

   float:
     m in [2^23, 2^24), value = m * 2^(e-23)
   double:
     m in [2^52, 2^53), value = m * 2^(e-52)

   This is intentionally minimal: it assumes m is in-range and nonzero.
   Caller handles sign separately (or pass signed m and use *_i* helpers).
*/

/**
 * Converts a given mantissa, exponent, and sign into a floating-point value.
 *
 * This function reconstructs a floating-point number from its components:
 * the mantissa (m), exponent (e), and sign. It directly encodes the result
 * if the exponent is within the range of normal float values; otherwise,
 * it adjusts the value using a scaling operation to handle edge cases.
 *
 * @param m The mantissa of the floating-point number. It must include the leading 1
 *          for normalized values, and only the lower 23 bits are used.
 * @param e The exponent value. It determines the power-of-two scaling for the result.
 * @param sign The sign of the floating-point number. Use 0 for positive and any non-zero
 *             value for negative.
 * @return A `float` value reconstructed from the specified mantissa, exponent, and sign.
 *         Returns signed zero for the case where the mantissa is zero.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_from_mantissa_exp(const uint32_t m, const int e, const int sign) {
    /* Start as a normal with exponent=e, then apply exact scaling if needed.
       We directly encode if e is in normal range; otherwise go through scalbn. */
    if(m == 0) {
        return ker_flt_signed_zero(sign);
    }

    /* m has leading 1 at bit 23; fraction field is low 23 bits */
    const uint32_t frac = m & FLT_FRAC_MASK;

    if(e >= -126 && e <= 127) {
        uint32_t out = ((uint32_t)(e + FLT_EXP_BIAS) << 23) | frac;
        if(sign) {
            out |= FLT_SIGN_MASK;
        }
        return ker_u32_to_flt(out);
    }

    /* Encode mantissa with exponent 0, then scale.
       Use m/2^23 in [1,2) by setting exponent to bias. */
    uint32_t base = ((uint32_t)FLT_EXP_BIAS << 23) | frac;
    if(sign) {
        base |= FLT_SIGN_MASK;
    }

    /* base = (m/2^23)*2^0. Need exponent e => scale by (e-0). */
    return ker_flt_scalbn(ker_u32_to_flt(base), e);
}

/**
 * Constructs a double-precision floating-point value from its mantissa, exponent, and sign.
 *
 * This function takes a mantissa, an exponent, and a sign to reconstruct a double-precision
 * floating-point value. It handles both normalized and subnormal forms as well as scaling
 * for exponents outside the normal range. Special handling is applied for zero mantissa values.
 *
 * @param m The mantissa of the double-precision number. Only the lower 52 bits are used.
 * @param e The exponent value, which determines the power-of-two scaling for the result.
 *          Valid input range includes subnormal, normal, and overflow conditions.
 * @param sign The sign of the resulting floating-point value. Use 0 for positive and any
 *             non-zero value for negative.
 * @return A `double` reconstructed from the given mantissa, exponent, and sign. Returns
 *         signed zero if the mantissa is zero, and handles special cases such as subnormal
 *         and overflow properly.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_from_mantissa_exp(const uint64_t m, const int e, const int sign) {
    if(m == 0) {
        return ker_dbl_signed_zero(sign);
    }

    const uint64_t frac = m & DBL_FRAC_MASK;

    if(e >= -1022 && e <= 1023) {
        uint64_t out = ((uint64_t)(e + DBL_EXP_BIAS) << 52) | frac;
        if(sign) {
            out |= DBL_SIGN_MASK;
        }
        return ker_u64_to_dbl(out);
    }

    uint64_t base = ((uint64_t)DBL_EXP_BIAS << 52) | frac;
    if(sign) {
        base |= DBL_SIGN_MASK;
    }

    return ker_dbl_scalbn(ker_u64_to_dbl(base), e);
}

#endif //LIBMA_FROM_MANTISSA_H
