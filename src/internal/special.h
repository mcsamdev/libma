//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_SPECIAL_H
#define LIBMA_SPECIAL_H

#include "fp_classify.h"

/* Canonical constants as bit patterns */

/* float */

#define FLT_POS_INF_U32 0x7F800000u
#define FLT_NEG_INF_U32 0xFF800000u
#define FLT_QNAN_U32    0x7FC00000u

/**
 * @brief Returns the 32-bit floating-point positive infinity value.
 *
 * This function converts a 32-bit unsigned integer representation of
 * positive infinity into a 32-bit floating-point representation and
 * returns the result.
 *
 * @return A positive infinity value in 32-bit floating-point format.
 */
LIBMA_ALWAYS_INLINE_STATIC float flt_pos_inf(void) {
    return u32_to_flt(FLT_POS_INF_U32);
}

/**
 * @brief Returns the 32-bit floating-point negative infinity value.
 *
 * This function converts a 32-bit unsigned integer representation of
 * negative infinity into a 32-bit floating-point representation and
 * returns the result.
 *
 * @return A negative infinity value in 32-bit floating-point format.
 */
LIBMA_ALWAYS_INLINE_STATIC float flt_neg_inf(void) {
    return u32_to_flt(FLT_NEG_INF_U32);
}

/**
 * @brief Returns the 32-bit floating-point quiet NaN (Not-a-Number) value.
 *
 * This function converts a 32-bit unsigned integer representation of
 * a quiet NaN into a 32-bit floating-point representation and returns
 * the result.
 *
 * @return A quiet NaN value in 32-bit floating-point format.
 */
LIBMA_ALWAYS_INLINE_STATIC float flt_qnan(void) {
    return u32_to_flt(FLT_QNAN_U32);
}

/**
 * @brief Converts a sign indicator into a 32-bit floating-point signed zero.
 *
 * This function generates a signed zero in 32-bit floating-point format
 * based on the provided sign indicator. If the sign is non-zero, the function
 * returns a negative zero; otherwise, it returns a positive zero.
 *
 * @param sign An integer value indicating the desired sign of the zero.
 *             A non-zero value results in a negative zero, while a zero value
 *             results in a positive zero.
 *
 * @return A 32-bit floating-point signed zero with the specified sign.
 */
LIBMA_ALWAYS_INLINE_STATIC float flt_signed_zero(const int sign) {
    return u32_to_flt((uint32_t)(sign != 0) << 31);
}

/* double */

#define DBL_POS_INF_U64 0x7FF0000000000000ULL
#define DBL_NEG_INF_U64 0xFFF0000000000000ULL
#define DBL_QNAN_U64    0x7FF8000000000000ULL

/**
 * @brief Returns the 64-bit floating-point positive infinity value.
 *
 * This function converts a 64-bit unsigned integer representation of
 * positive infinity into a 64-bit floating-point representation and
 * returns the result.
 *
 * @return A positive infinity value in 64-bit floating-point format.
 */
LIBMA_ALWAYS_INLINE_STATIC double dbl_pos_inf(void) {
    return u64_to_dbl(DBL_POS_INF_U64);
}

/**
 * @brief Returns the 64-bit floating-point negative infinity value.
 *
 * This function converts a 64-bit unsigned integer representation of
 * negative infinity into a 64-bit floating-point representation and
 * returns the result.
 *
 * @return A negative infinity value in 64-bit floating-point format.
 */
LIBMA_ALWAYS_INLINE_STATIC double dbl_neg_inf(void) {
    return u64_to_dbl(DBL_NEG_INF_U64);
}

/**
 * @brief Returns the 64-bit floating-point quiet NaN (Not-a-Number) value.
 *
 * This function produces a quiet NaN value in 64-bit floating-point format
 * by converting a predetermined 64-bit unsigned integer representation of
 * quiet NaN into its corresponding floating-point representation.
 *
 * @return A quiet NaN value in 64-bit floating-point format.
 */
LIBMA_ALWAYS_INLINE_STATIC double dbl_qnan(void) {
    return u64_to_dbl(DBL_QNAN_U64);
}

/**
 * @brief Returns a signed zero in double-precision floating-point format.
 *
 * This function generates a double-precision signed zero based on the given sign.
 * If the sign is non-zero, the result will be a negative zero; otherwise, it will be a positive zero.
 *
 * @param sign An integer representing the sign of the zero. A non-zero value results in negative zero, and zero results in positive zero.
 * @return A double-precision signed zero, either positive or negative, based on the sign.
 */
LIBMA_ALWAYS_INLINE_STATIC double dbl_signed_zero(const int sign) {
    return u64_to_dbl((uint64_t)(sign != 0) << 63);
}

#endif //LIBMA_SPECIAL_H
