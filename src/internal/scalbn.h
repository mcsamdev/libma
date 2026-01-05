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
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_scalbn(const float x, const int k) {
    const uint32_t u = ker_flt_to_u32(x);
    const uint32_t ax = u & ~FLT_SIGN_MASK;
    const uint32_t sign = u & FLT_SIGN_MASK;

    /* NaN/Inf/Zero => return x+x to preserve NaN payload propagation behavior */
    if(ax >= FLT_EXP_MASK) {
        return x + x;
    }
    if(ax == 0) {
        return x; /* signed zero */
    }

    const int exp = ker_flt_exp_u32(ax);
    const uint32_t frac = ker_flt_frac_u32(ax);

    if(exp == 0) {
        /* subnormal: normalize then apply k */
        int e;
        const uint32_t m = ker_flt_mantissa_u32(ker_u32_to_flt(sign | frac), &e); /* positive subnormal */
        /* x = m * 2^(e-23); scaling by k => exponent becomes (e+k) */
        e += k;

        /* convert to normal/subnormal */
        if(e > 127) {
            return ker_u32_to_flt(sign | FLT_POS_INF_U32); /* overflow */
        }
        if(e < -149) {
            return ker_u32_to_flt(sign); /* underflow to signed zero */
        }

        if(e >= -126) {
            /* normal: exponent field = e + bias, frac = (m - 2^23) */
            const auto out_exp = (uint32_t)(e + FLT_EXP_BIAS);
            const uint32_t out_frac = (m & FLT_FRAC_MASK);
            return ker_u32_to_flt(sign | (out_exp << 23) | out_frac);
        }
        /* subnormal: value = m * 2^(e-23), with e < -126
               shift right to place into subnormal fraction domain. */
        const int rshift = (-126 - e);
        /* m has leading 1 at bit 23, need to shift into [22:0] with exponent 0 */
        const uint32_t sub = m >> rshift;
        return ker_u32_to_flt(sign | (sub & FLT_FRAC_MASK));
    }

    /* normal */
    int e = exp - FLT_EXP_BIAS;
    e += k;

    if(e > 127) {
        return ker_u32_to_flt(sign | FLT_POS_INF_U32); /* overflow */
    }
    if(e < -149) {
        return ker_u32_to_flt(sign); /* underflow to signed zero */
    }

    if(e >= -126) {
        const auto out_exp = (uint32_t)(e + FLT_EXP_BIAS);
        return ker_u32_to_flt(sign | (out_exp << 23) | frac);
    }
    /* underflow to subnormal */
    /* construct mantissa with implicit 1 then shift */
    const uint32_t m = (1u << 23) | frac;
    const int rshift = (-126 - e);
    const uint32_t sub = m >> rshift;
    return ker_u32_to_flt(sign | (sub & FLT_FRAC_MASK));
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
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_scalbn(const double x, const int k) {
    const uint64_t u = ker_dbl_to_u64(x);
    const uint64_t ax = u & ~DBL_SIGN_MASK;
    const uint64_t sign = u & DBL_SIGN_MASK;

    if(ax >= DBL_EXP_MASK) {
        return x + x; /* NaN/Inf */
    }
    if(ax == 0) {
        return x; /* signed zero */
    }

    const int exp = ker_dbl_exp_u64(ax);
    const uint64_t frac = ker_dbl_frac_u64(ax);

    if(exp == 0) {
        /* subnormal: normalize then apply k */
        int e;
        const uint64_t m = ker_dbl_mantissa_u64(ker_u64_to_dbl(sign | frac), &e); /* positive subnormal */
        e += k;

        if(e > 1023) {
            return ker_u64_to_dbl(sign | DBL_POS_INF_U64); /* overflow */
        }
        if(e < -1074) {
            return ker_u64_to_dbl(sign); /* underflow to signed zero */
        }

        if(e >= -1022) {
            const auto out_exp = (uint64_t)(e + DBL_EXP_BIAS);
            const uint64_t out_frac = (m & DBL_FRAC_MASK);
            return ker_u64_to_dbl(sign | (out_exp << 52) | out_frac);
        }
        const int rshift = (-1022 - e);
        const uint64_t sub = m >> rshift;
        return ker_u64_to_dbl(sign | (sub & DBL_FRAC_MASK));
    }

    int e = exp - DBL_EXP_BIAS;
    e += k;

    if(e > 1023) {
        return ker_u64_to_dbl(sign | DBL_POS_INF_U64);
    }
    if(e < -1074) {
        return ker_u64_to_dbl(sign);
    }

    if(e >= -1022) {
        const auto out_exp = (uint64_t)(e + DBL_EXP_BIAS);
        return ker_u64_to_dbl(sign | (out_exp << 52) | frac);
    }
    const uint64_t m = (1ULL << 52) | frac;
    const int rshift = (-1022 - e);
    const uint64_t sub = m >> rshift;
    return ker_u64_to_dbl(sign | (sub & DBL_FRAC_MASK));
}

/**
 * Decomposes a floating-point number into its binary significand (range [0.5, 1.0))
 * and an integral exponent.
 *
 * @param x The floating-point value to be decomposed.
 * @param e Pointer to an integer where the exponent will be stored.
 * @return The significand part of x. If x is zero, returns x and sets *e to 0.
 *         If x is Inf or NaN, returns x and sets *e to 0.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_frexp(const float x, int* e) {
    const uint32_t u = ker_flt_to_u32(x);
    const uint32_t sign = u & FLT_SIGN_MASK;
    const uint32_t ax = u & ~FLT_SIGN_MASK;

    if(ax >= FLT_EXP_MASK || ax == 0) {
        *e = 0;
        return x;
    }

    int e_int;
    const uint32_t m = ker_flt_mantissa_u32(x, &e_int);
    *e = e_int + 1;

    const uint32_t frac_bits = m & FLT_FRAC_MASK;
    constexpr uint32_t exp_bits = (uint32_t)(FLT_EXP_BIAS - 1) << 23;
    return ker_u32_to_flt(sign | exp_bits | frac_bits);
}

/**
 * Decomposes a double-precision floating-point number into its significand (range [0.5, 1.0))
 * and an integral exponent.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_frexp(const double x, int* e) {
    const uint64_t u = ker_dbl_to_u64(x);
    const uint64_t sign = u & DBL_SIGN_MASK;
    const uint64_t ax = u & ~DBL_SIGN_MASK;

    if(ax >= DBL_EXP_MASK || ax == 0) {
        *e = 0;
        return x;
    }

    int e_int;
    const uint64_t m = ker_dbl_mantissa_u64(x, &e_int);
    *e = e_int + 1;

    const uint64_t frac_bits = m & DBL_FRAC_MASK;
    constexpr uint64_t exp_bits = (uint64_t)(DBL_EXP_BIAS - 1) << 52;
    return ker_u64_to_dbl(sign | exp_bits | frac_bits);
}

/**
 * Returns the binary exponent of a floating-point value as a signed integer.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_flt_ilogb(const float x) {
    const uint32_t u = ker_flt_to_u32(x);
    const uint32_t ax = u & ~FLT_SIGN_MASK;
    if(ax == 0) {
        return LIBMA_FP_ILOGB0;
    }
    if(ax > FLT_EXP_MASK) {
        return LIBMA_FP_ILOGBNAN;
    }
    if(ax == FLT_EXP_MASK) {
        return INT_MAX;
    }

    int e;
    ker_flt_mantissa_u32(x, &e);
    return e;
}

/**
 * Returns the binary exponent of a double-precision floating-point value as a signed integer.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_ilogb(const double x) {
    const uint64_t u = ker_dbl_to_u64(x);
    const uint64_t ax = u & ~DBL_SIGN_MASK;
    if(ax == 0) {
        return LIBMA_FP_ILOGB0;
    }
    if(ax > DBL_EXP_MASK) {
        return LIBMA_FP_ILOGBNAN;
    }
    if(ax == DBL_EXP_MASK) {
        return INT_MAX;
    }

    int e;
    ker_dbl_mantissa_u64(x, &e);
    return e;
}

/**
 * Returns the binary exponent of a floating-point value as a floating-point value.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_logb(const float x) {
    const uint32_t u = ker_flt_to_u32(x);
    const uint32_t ax = u & ~FLT_SIGN_MASK;
    if(ax == 0) {
        return ker_flt_neg_inf();
    }
    if(ax >= FLT_EXP_MASK) {
        // IEEE 754: return NaN for NaN, Inf for Inf.
        // Using quiet_nan ensures sNaNs don't trap unnecessarily.
        if(ker_flt_isnan_u32(ax)) {
            return ker_u32_to_flt(ker_flt_quiet_nan_u32(u));
        }
        return ker_flt_pos_inf();
    }

    int e;
    ker_flt_mantissa_u32(x, &e);
    return (float)e;
}

/**
 * Returns the binary exponent of a double-precision floating-point value as a floating-point value.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_logb(const double x) {
    const uint64_t u = ker_dbl_to_u64(x);
    const uint64_t ax = u & ~DBL_SIGN_MASK;
    if(ax == 0) {
        return ker_dbl_neg_inf();
    }
    if(ax >= FLT_EXP_MASK) {
        // IEEE 754: return NaN for NaN, Inf for Inf.
        // Using quiet_nan ensures sNaNs don't trap unnecessarily.
        if(ker_dbl_isnan_u64(ax)) {
            return ker_u64_to_dbl(ker_dbl_quiet_nan_u64(u));
        }
        return ker_dbl_pos_inf();
    }

    int e;
    ker_dbl_mantissa_u64(x, &e);
    return (double)e;
}

#endif //LIBMA_SCALBN_H
