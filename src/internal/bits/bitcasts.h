//
// Created by sammc on 1/21/26.
//
#pragma once
#ifndef LIBMA_BITCASTS_H
#define LIBMA_BITCASTS_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "libma_def.h"
/**
 * @brief Converts a 32-bit floating-point value to a 32-bit unsigned integer
 *        by performing a bitwise reinterpretation of the memory.
 *
 * @param f The 32-bit floating-point value to be converted.
 * @return The 32-bit unsigned integer representation of the input value.
 */
KER_PURE_INLINE u32 f32_to_u32(const f32 f) {
    u32 u;
    LIBMA_MEMCPY(&u, &f, sizeof(f));
    return u;
}

/**
 * @brief Converts a 32-bit unsigned integer to a 32-bit floating-point value
 *        by performing a bitwise reinterpretation of the memory.
 *
 * @param u The 32-bit unsigned integer value to be converted.
 * @return The 32-bit floating-point representation of the input value.
 */
KER_PURE_INLINE f32 u32_to_f32(const u32 u) {
    f32 f;
    LIBMA_MEMCPY(&f, &u, sizeof(u));
    return f;
}

/**
 * @brief Converts a 64-bit floating-point value to a 64-bit unsigned integer
 *        through a bitwise reinterpretation of the memory.
 *
 * @param f The 64-bit floating-point value to be converted.
 * @return The 64-bit unsigned integer representation of the input value.
 */
KER_CONST_INLINE u64 f64_to_u64(const f64 f) {
    u64 u;
    LIBMA_MEMCPY(&u, &f, sizeof(f));
    return u;
}

/**
 * @brief Converts a 64-bit unsigned integer value to a 64-bit floating-point
 *        value by performing a bitwise reinterpretation of the memory.
 *
 * @param u The 64-bit unsigned integer value to be converted.
 * @return The 64-bit floating-point representation of the input value.
 */
KER_PURE_INLINE f64 u64_to_f64(const u64 u) {
    f64 f;
    LIBMA_MEMCPY(&f, &u, sizeof(u));
    return f;
}

#endif // LIBMA_BITCASTS_H
