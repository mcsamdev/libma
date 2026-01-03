//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_FP_CLASSIFY_H
#define LIBMA_FP_CLASSIFY_H

#include "bits.h"

/* --- float (binary32) --- */
/**
 * Checks if the given 32-bit unsigned integer representation of a floating-point number
 * corresponds to a NaN (Not-a-Number) value in the IEEE 754 single-precision format.
 *
 * @param u The 32-bit unsigned integer representing a floating-point number.
 * @return True if the number is NaN, false otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC bool ker_flt_isnan_u32(const uint32_t u) {
    return (u & FLT_EXP_MASK) == FLT_EXP_MASK && (u & FLT_FRAC_MASK) != 0;
}

/**
 * Checks if the given 32-bit unsigned integer representation of a floating-point number
 * corresponds to an infinity value in the IEEE 754 single-precision format.
 *
 * @param u The 32-bit unsigned integer representing a floating-point number.
 * @return True if the number represents positive or negative infinity, false otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC bool ker_flt_isinf_u32(const uint32_t u) {
    return (u & (FLT_EXP_MASK | FLT_FRAC_MASK)) == FLT_EXP_MASK;
}

/**
 * Determines whether the given 32-bit unsigned integer representation of a floating-point number
 * corresponds to a finite value in the IEEE 754 single-precision format.
 *
 * @param u The 32-bit unsigned integer representing a floating-point number.
 * @return True if the number is finite, false otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC bool ker_flt_isfinite_u32(const uint32_t u) {
    return (u & FLT_EXP_MASK) != FLT_EXP_MASK;
}

/**
 * Determines whether a given 32-bit unsigned integer representation of a
 * floating-point number corresponds to zero (positive or negative) in the
 * IEEE 754 single-precision format.
 *
 * @param u The 32-bit unsigned integer representing a floating-point number.
 * @return True if the number is zero (ignoring its sign), false otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC bool ker_flt_iszero_u32(const uint32_t u) {
    return (u & ~FLT_SIGN_MASK) == 0;
}

/**
 * Determines if the given 32-bit unsigned integer representation of a floating-point number
 * corresponds to a subnormal value in the IEEE 754 single-precision format.
 *
 * @param u The 32-bit unsigned integer representing a floating-point number.
 * @return True if the number is subnormal, false otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC bool ker_flt_issubnormal_u32(const uint32_t u) {
    return (u & FLT_EXP_MASK) == 0 && (u & FLT_FRAC_MASK) != 0;
}

/**
 * Creates a new floating-point value with the magnitude of the first argument and
 * the sign of the second argument, preserving their respective components.
 *
 * @param x The floating-point value from which the magnitude is taken.
 * @param y The floating-point value from which the sign bit is taken.
 * @return A floating-point value with the magnitude of x and the sign of y.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_copysign(const float x, const float y) {
    uint32_t ux = ker_flt_to_u32(x);
    uint32_t uy = ker_flt_to_u32(y);
    ux = (ux & ~FLT_SIGN_MASK) | (uy & FLT_SIGN_MASK);
    return ker_u32_to_flt(ux);
}

/**
 * Computes the absolute value of a floating-point number by clearing its sign bit.
 *
 * @param x The input floating-point number.
 * @return The absolute value of the input floating-point number.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_fabs(const float x) {
    uint32_t u = ker_flt_to_u32(x);
    u &= ~FLT_SIGN_MASK;
    return ker_u32_to_flt(u);
}

/**
 * Computes the negation of the given floating-point number by flipping its sign bit
 * in the IEEE 754 single-precision binary representation.
 *
 * @param x The floating-point number to negate.
 * @return The negated floating-point number.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_flt_neg(const float x) {
    uint32_t u = ker_flt_to_u32(x);
    u ^= FLT_SIGN_MASK;
    return ker_u32_to_flt(u);
}

/* quiet a NaN: set MSB of fraction (common qNaN bit) */
/**
 * Converts the given 32-bit unsigned integer representation of a floating-point number
 * to its quiet NaN (Not-a-Number) representation in the IEEE 754 single-precision format.
 *
 * @param u The 32-bit unsigned integer representing a floating-point number.
 * @return The 32-bit unsigned integer representation of a quiet NaN.
 */
LIBMA_ALWAYS_INLINE_STATIC uint32_t ker_flt_quiet_nan_u32(const uint32_t u) {
    return u | 1u << 22;
}

/* --- double (binary64) --- */
/**
 * Determines if the given 64-bit unsigned integer representation of a floating-point number
 * corresponds to a NaN (Not-a-Number) value in the IEEE 754 double-precision format.
 *
 * @param u The 64-bit unsigned integer representing a double-precision floating-point number.
 * @return Non-zero if the number is NaN, zero otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_isnan_u64(const uint64_t u) {
    return (u & DBL_EXP_MASK) == DBL_EXP_MASK && (u & DBL_FRAC_MASK) != 0;
}

/**
 * Determines whether the given 64-bit unsigned integer representation of a
 * floating-point number corresponds to infinity in the IEEE 754 double-precision format.
 *
 * @param u The 64-bit unsigned integer representing a floating-point number.
 * @return Nonzero if the number represents positive or negative infinity, 0 otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_isinf_u64(const uint64_t u) {
    return (u & (DBL_EXP_MASK | DBL_FRAC_MASK)) == DBL_EXP_MASK;
}

/**
 * Determines whether the given 64-bit unsigned integer representation of
 * a floating-point number corresponds to a finite value in the IEEE 754
 * double-precision format.
 *
 * @param u The 64-bit unsigned integer representing a floating-point number.
 * @return Non-zero if the number is finite, zero if it is either infinite or NaN.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_isfinite_u64(const uint64_t u) {
    return (u & DBL_EXP_MASK) != DBL_EXP_MASK;
}

/**
 * Determines if the given 64-bit unsigned integer representation of a floating-point number
 * corresponds to a zero value in the IEEE 754 double-precision format, ignoring the sign bit.
 *
 * @param u The 64-bit unsigned integer representing a floating-point number.
 * @return Non-zero value if the number is zero, otherwise 0.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_iszero_u64(const uint64_t u) {
    return (u & ~DBL_SIGN_MASK) == 0;
}

/**
 * Determines if the given 64-bit unsigned integer representation of a floating-point number
 * corresponds to a subnormal value in the IEEE 754 double-precision format.
 *
 * @param u The 64-bit unsigned integer representing a floating-point number.
 * @return Non-zero if the number is subnormal, zero otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_issubnormal_u64(const uint64_t u) {
    return (u & DBL_EXP_MASK) == 0 && (u & DBL_FRAC_MASK) != 0;
}

/**
 * Copies the sign of one double-precision floating-point number to another.
 *
 * This function takes two double-precision floating-point numbers and returns a new number
 * with the magnitude of the first number and the sign of the second number.
 *
 * @param x The double-precision floating-point number whose magnitude is to be retained.
 * @param y The double-precision floating-point number whose sign is to be copied.
 * @return A double-precision floating-point number with the magnitude of x and the sign of y.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_copysign(const double x, const double y) {
    uint64_t ux = ker_dbl_to_u64(x);
    const uint64_t uy = ker_dbl_to_u64(y);
    ux = (ux & ~DBL_SIGN_MASK) | (uy & DBL_SIGN_MASK);
    return ker_u64_to_dbl(ux);
}

/**
 * Computes the absolute value of a double-precision floating-point number.
 *
 * This method removes the sign bit from the IEEE 754 representation of the
 * input number to ensure the result is non-negative.
 *
 * @param x The input double-precision floating-point number.
 * @return The absolute value of the input as a double-precision floating-point number.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_fabs(const double x) {
    uint64_t u = ker_dbl_to_u64(x);
    u &= ~DBL_SIGN_MASK;
    return ker_u64_to_dbl(u);
}

/**
 * Returns the negation of the given double-precision floating-point number.
 * This is achieved by flipping the sign bit of the input value's IEEE 754 representation.
 *
 * @param x The double-precision floating-point number to negate.
 * @return The negated double-precision floating-point number.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_dbl_neg(const double x) {
    uint64_t u = ker_dbl_to_u64(x);
    u ^= DBL_SIGN_MASK;
    return ker_u64_to_dbl(u);
}

/**
 * Converts the given 64-bit unsigned integer representation of a double-precision
 * floating-point number to its quiet NaN (Not-a-Number) form in the IEEE 754 format.
 * This is done by setting the quiet bit in the significand.
 *
 * @param u The 64-bit unsigned integer representing a double-precision floating-point number.
 * @return The 64-bit unsigned integer representation of the quiet NaN form.
 */
LIBMA_ALWAYS_INLINE_STATIC uint64_t ker_dbl_quiet_nan_u64(const uint64_t u) {
    return u | 1ULL << 51;
}

/* Convenience wrappers operating on float/double directly */
/**
 * Determines whether the given floating-point number is a NaN (Not-a-Number) value
 * according to the IEEE 754 single-precision format.
 *
 * @param x The floating-point number to be checked.
 * @return Non-zero if the number is NaN, otherwise zero.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_flt_isnan(const float x) {
    return ker_flt_isnan_u32(ker_flt_to_u32(x));
}

/**
 * Determines whether the given floating-point number is infinite (positive or negative infinity)
 * according to the IEEE 754 single-precision format.
 *
 * @param x The floating-point number to check.
 * @return Non-zero if the number is infinite, 0 otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_flt_isinf(const float x) {
    return ker_flt_isinf_u32(ker_flt_to_u32(x));
}

/**
 * Determines whether the given floating-point number is finite
 * (i.e., not infinity or NaN) in single-precision format.
 *
 * @param x The floating-point number to check.
 * @return 1 if the number is finite, 0 otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_flt_isfinite(const float x) {
    return ker_flt_isfinite_u32(ker_flt_to_u32(x));
}

/**
 * Determines if the given floating-point number is equal to zero.
 *
 * @param x The floating-point number to evaluate.
 * @return Non-zero integer if the number is zero, zero otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_flt_iszero(const float x) {
    return ker_flt_iszero_u32(ker_flt_to_u32(x));
}

/**
 * Determines if the given floating-point number is a subnormal value
 * (denormalized number) in the IEEE 754 single-precision format.
 *
 * @param x The floating-point number to check.
 * @return Non-zero (true) if the number is subnormal, 0 (false) otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_flt_issubnormal(const float x) {
    return ker_flt_issubnormal_u32(ker_flt_to_u32(x));
}

/**
 * Determines if the given double-precision floating-point number corresponds to
 * a NaN (Not-a-Number) value in the IEEE 754 double-precision format.
 *
 * @param x The double-precision floating-point number to check.
 * @return A non-zero value if the number is NaN, zero otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_isnan(const double x) {
    return ker_dbl_isnan_u64(ker_dbl_to_u64(x));
}

/**
 * Determines if the given double-precision floating-point number represents
 * infinity in the IEEE 754 format.
 *
 * @param x The double-precision floating-point number to check.
 * @return Non-zero if the number is infinity (positive or negative), zero otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_isinf(const double x) {
    return ker_dbl_isinf_u64(ker_dbl_to_u64(x));
}

/**
 * Determines if the given double-precision floating-point number is finite
 * (not positive infinity, negative infinity, or NaN) based on IEEE 754 format.
 *
 * @param x The double-precision floating-point number to check.
 * @return Non-zero if the number is finite, zero otherwise.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_isfinite(const double x) {
    return ker_dbl_isfinite_u64(ker_dbl_to_u64(x));
}

/**
 * Determines whether the given double-precision floating-point number is zero.
 *
 * @param x The double-precision floating-point number to be checked.
 * @return Non-zero if the number is zero, otherwise 0.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_iszero(const double x) {
    return ker_dbl_iszero_u64(ker_dbl_to_u64(x));
}

/**
 * Determines whether the given double-precision floating-point value is a subnormal number.
 * A subnormal number in IEEE 754 format is one where the exponent is all zeros and
 * the fraction is non-zero, representing values that are very close to zero.
 *
 * @param x The double-precision floating-point number to classify.
 * @return Non-zero if the number is subnormal, otherwise zero.
 */
LIBMA_ALWAYS_INLINE_STATIC int ker_dbl_issubnormal(const double x) {
    return ker_dbl_issubnormal_u64(ker_dbl_to_u64(x));
}

#endif //LIBMA_FP_CLASSIFY_H
