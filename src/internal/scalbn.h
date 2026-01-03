//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_SCALBN_H
#define LIBMA_SCALBN_H

#include "fp_classify.h"
#include "mantissa.h"
#include "special.h"
// This just gets called in the source files but is still here since is used everywhere

/* Build x * 2^k efficiently with correct IEEE-754 behavior for binary32/binary64.
   This is the primitive behind scalbn/ldexp and is also handy for kernels.

   Semantics:
   - Preserves NaN payloads and Inf.
   - Preserves signed zero.
   - Produces subnormals on underflow, +/-0 when too small.
   - Produces +/-Inf on overflow.
*/
/**
 * Adjusts the floating-point value by scaling its binary exponent by a specified integer value.
 *
 * This function computes `x * 2^k` by manipulating the underlying representation of the floating-point
 * number. It handles subnormal numbers, overflows, and underflows according to IEEE 754 behavior.
 *
 * @param x The floating-point value to be scaled.
 * @param k The integer exponent by which to scale the floating-point value.
 * @return The floating-point result of scaling `x` by `2^k`. Returns:
 *         - `NaN` if `x` is `NaN`.
 *         - `+Infinity` or `-Infinity` on overflow.
 *         - `+0` or `-0` on underflow.
 *         - The scaled result otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC float flt_scalbn(const float x, const int k) {
    const uint32_t u = flt_to_u32(x);
    const uint32_t ax = u & ~FLT_SIGN_MASK;
    const uint32_t sign = u & FLT_SIGN_MASK;

    /* NaN/Inf/Zero => return x+x to preserve NaN payload propagation behavior */
    if(ax >= FLT_EXP_MASK) {
        return x + x;
    }
    if(ax == 0) {
        return x; /* signed zero */
    }

    const auto exp = (int)((ax >> 23) & 0xFF);
    const uint32_t frac = ax & FLT_FRAC_MASK;

    if(exp == 0) {
        /* subnormal: normalize then apply k */
        int e;
        const uint32_t m = flt_mantissa_u32(u32_to_flt(sign | frac), &e); /* positive subnormal */
        /* x = m * 2^(e-23); scaling by k => exponent becomes (e+k) */
        e += k;

        /* convert to normal/subnormal */
        if(e > 127) {
            return u32_to_flt(sign | FLT_POS_INF_U32); /* overflow */
        }
        if(e < -149) {
            return u32_to_flt(sign); /* underflow to signed zero */
        }

        if(e >= -126) {
            /* normal: exponent field = e + bias, frac = (m - 2^23) */
            const auto out_exp = (uint32_t)(e + FLT_EXP_BIAS);
            const uint32_t out_frac = (m & FLT_FRAC_MASK);
            return u32_to_flt(sign | (out_exp << 23) | out_frac);
        }
        else {
            /* subnormal: value = m * 2^(e-23), with e < -126
               shift right to place into subnormal fraction domain. */
            const int rshift = (-126 - e);
            /* m has leading 1 at bit 23, need to shift into [22:0] with exponent 0 */
            const uint32_t sub = m >> rshift;
            return u32_to_flt(sign | (sub & FLT_FRAC_MASK));
        }
    }

    /* normal */
    int e = exp - FLT_EXP_BIAS;
    e += k;

    if(e > 127) {
        return u32_to_flt(sign | FLT_POS_INF_U32); /* overflow */
    }
    if(e < -149) {
        return u32_to_flt(sign); /* underflow to signed zero */
    }

    if(e >= -126) {
        const auto out_exp = (uint32_t)(e + FLT_EXP_BIAS);
        return u32_to_flt(sign | (out_exp << 23) | frac);
    }
    /* underflow to subnormal */
    /* construct mantissa with implicit 1 then shift */
    const uint32_t m = (1u << 23) | frac;
    const int rshift = (-126 - e);
    const uint32_t sub = m >> rshift;
    return u32_to_flt(sign | (sub & FLT_FRAC_MASK));
}

/**
 * Scales a floating-point value by adjusting its binary exponent by a specified integer value.
 *
 * This function computes `x * 2^k` by directly manipulating the representation of the
 * floating-point value. It addresses special cases such as subnormal numbers, signed zero,
 * overflows, and underflows according to IEEE 754 semantics.
 *
 * @param x The double-precision floating-point value to be scaled.
 * @param k The integer exponent adjustment to scale the floating-point value by.
 *        Positive values increase the magnitude, and negative values decrease it.
 * @return The double-precision floating-point result of scaling `x` by `2^k`.
 *         Returns:
 *         - `NaN` if `x` is not-a-number (NaN).
 *         - `+Infinity` or `-Infinity` if the result overflows.
 *         - `+0` or `-0` if the result underflows.
 *         - The appropriately scaled value otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC double dbl_scalbn(const double x, const int k) {
    const uint64_t u = dbl_to_u64(x);
    const uint64_t ax = u & ~DBL_SIGN_MASK;
    const uint64_t sign = u & DBL_SIGN_MASK;

    if(ax >= DBL_EXP_MASK) {
        return x + x; /* NaN/Inf */
    }
    if(ax == 0) {
        return x; /* signed zero */
    }

    const auto exp = (int)((ax >> 52) & 0x7FF);
    const uint64_t frac = ax & DBL_FRAC_MASK;

    if(exp == 0) {
        /* subnormal: normalize then apply k */
        int e;
        const uint64_t m = dbl_mantissa_u64(u64_to_dbl(sign | frac), &e); /* positive subnormal */
        e += k;

        if(e > 1023) {
            return u64_to_dbl(sign | DBL_POS_INF_U64); /* overflow */
        }
        if(e < -1074) {
            return u64_to_dbl(sign); /* underflow to signed zero */
        }

        if(e >= -1022) {
            const auto out_exp = (uint64_t)(e + DBL_EXP_BIAS);
            const uint64_t out_frac = (m & DBL_FRAC_MASK);
            return u64_to_dbl(sign | (out_exp << 52) | out_frac);
        }
        const int rshift = (-1022 - e);
        const uint64_t sub = m >> rshift;
        return u64_to_dbl(sign | (sub & DBL_FRAC_MASK));
    }

    int e = exp - DBL_EXP_BIAS;
    e += k;

    if(e > 1023) {
        return u64_to_dbl(sign | DBL_POS_INF_U64);
    }
    if(e < -1074) {
        return u64_to_dbl(sign);
    }

    if(e >= -1022) {
        const auto out_exp = (uint64_t)(e + DBL_EXP_BIAS);
        return u64_to_dbl(sign | (out_exp << 52) | frac);
    }
    const uint64_t m = (1ULL << 52) | frac;
    const int rshift = (-1022 - e);
    const uint64_t sub = m >> rshift;
    return u64_to_dbl(sign | (sub & DBL_FRAC_MASK));
}

#endif //LIBMA_SCALBN_H
