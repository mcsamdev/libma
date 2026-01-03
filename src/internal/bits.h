//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_BITS_H
#define LIBMA_BITS_H

#include <string.h>
#include "math_config.h"

/* --- bit-casts (portable, optimizer-friendly) --- */

/**
 * Converts a floating-point number to its raw 32-bit unsigned integer
 * representation by preserving the exact bit pattern of the float.
 *
 * @param x The floating-point number to convert.
 * @return The 32-bit unsigned integer representation of the floating-point number.
 */
LIBMA_ALWAYS_INLINE_STATIC uint32_t flt_to_u32(const float x) {
    uint32_t u;
#if LIBMA_BUILTIN_MEMCPY
    __builtin_memcpy(&u, &x, sizeof u);
#else
    memcpy(&u, &x, sizeof u);
#endif
    return u;
}

/**
 * Converts a 32-bit unsigned integer into its equivalent floating-point
 * representation by interpreting the bit pattern as a float.
 *
 * @param u The 32-bit unsigned integer to convert.
 * @return The floating-point representation of the given unsigned integer.
 */
LIBMA_ALWAYS_INLINE_STATIC float u32_to_flt(const uint32_t u) {
    float x;
#if LIBMA_BUILTIN_MEMCPY
    __builtin_memcpy(&x, &u, sizeof x);
#else
    memcpy(&x, &u, sizeof x);
#endif
    return x;
}

/**
 * Converts a double-precision floating-point number to its raw 64-bit unsigned
 * integer representation by preserving the exact bit pattern of the double.
 *
 * @param x The double-precision floating-point number to convert.
 * @return The 64-bit unsigned integer representation of the double-precision
 *         floating-point number.
 */
LIBMA_ALWAYS_INLINE_STATIC uint64_t dbl_to_u64(const double x) {
    uint64_t u;
#if LIBMA_BUILTIN_MEMCPY
    __builtin_memcpy(&u, &x, sizeof u);
#else
    memcpy(&u, &x, sizeof u);
#endif
    return u;
}

/**
 * Converts a 64-bit unsigned integer to its raw double-precision floating-point
 * representation by preserving the exact bit pattern of the input.
 *
 * @param u The 64-bit unsigned integer to convert.
 * @return The double-precision floating-point representation of the input.
 */
LIBMA_ALWAYS_INLINE_STATIC double u64_to_dbl(const uint64_t u) {
    double x;
#if LIBMA_BUILTIN_MEMCPY
    __builtin_memcpy(&x, &u, sizeof x);
#else
    memcpy(&x, &u, sizeof x);
#endif
    return x;
}

/* --- IEEE-754 binary32 layout --- */

#define FLT_SIGN_MASK  0x80000000u
#define FLT_EXP_MASK   0x7F800000u
#define FLT_FRAC_MASK  0x007FFFFFu
#define FLT_EXP_BIAS   127
/**
 * Extracts the sign bit from a 32-bit unsigned integer representation of a floating-point number.
 *
 * @param u The 32-bit unsigned integer representation of a floating-point number.
 * @return The sign of the floating-point number, where 0 indicates positive and 1 indicates negative.
 */
LIBMA_ALWAYS_INLINE_STATIC int flt_sign_u32(const uint32_t u) {
    return (int)(u >> 31);
}

/**
 * Extracts the exponent part of a 32-bit floating-point number, represented
 * as an unsigned 32-bit integer, according to the IEEE 754 standard.
 *
 * @param u The 32-bit unsigned integer representation of the floating-point number.
 * @return The exponent value as a signed integer.
 */
LIBMA_ALWAYS_INLINE_STATIC int flt_exp_u32(const uint32_t u) {
    return (int)((u >> 23) & 0xFF);
}

/**
 * Extracts the fractional part of a 32-bit unsigned integer representation
 * of a floating-point number by masking all bits except the fraction bits.
 *
 * @param u The 32-bit unsigned integer representation of a floating-point number.
 * @return The fractional part of the floating-point number as a 32-bit unsigned integer.
 */
LIBMA_ALWAYS_INLINE_STATIC uint32_t flt_frac_u32(const uint32_t u) {
    return u & FLT_FRAC_MASK;
}

/* --- IEEE-754 binary64 layout --- */

#define DBL_SIGN_MASK  0x8000000000000000ULL
#define DBL_EXP_MASK   0x7FF0000000000000ULL
#define DBL_FRAC_MASK  0x000FFFFFFFFFFFFFULL
#define DBL_EXP_BIAS   1023
/**
 * Extracts the sign bit from a 64-bit unsigned integer by shifting
 * the most significant bit (MSB) to the least significant position.
 *
 * @param u The 64-bit unsigned integer to extract the sign bit from.
 * @return An integer representing the sign bit: 1 if the MSB is set, 0 otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int dbl_sign_u64(const uint64_t u) {
    return (int)(u >> 63);
}

/**
 * Extracts the exponent part of a 64-bit raw double-precision
 * floating-point number representation.
 *
 * The returned value corresponds to the unbiased exponent
 * (11-bit field) encoded within the given 64-bit representation.
 *
 * @param u The 64-bit unsigned integer representing the raw
 *          double-precision floating-point bit pattern.
 * @return The extracted exponent value as a signed integer.
 */
LIBMA_ALWAYS_INLINE_STATIC int dbl_exp_u64(const uint64_t u) {
    return (int)((u >> 52) & 0x7FF);
}

/**
 * Extracts the fractional part of a double-precision floating-point number,
 * represented as its 64-bit unsigned integer encoding, by masking out all
 * bits except those corresponding to the fraction (mantissa).
 *
 * @param u The 64-bit unsigned integer representation of a double-precision
 * floating-point number.
 * @return The 64-bit unsigned integer fractional part of the input.
 */
LIBMA_ALWAYS_INLINE_STATIC uint64_t dbl_frac_u64(const uint64_t u) {
    return u & DBL_FRAC_MASK;
}

#endif //LIBMA_BITS_H
