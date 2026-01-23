//
// Created by sammc on 1/23/26.
//
#include "libma.h"
#include "libma_def.h"
#include "bits/bitcasts.h"
#include "bits/consts.h"

int totalorder(const double* x, const double* y) {
    // use manual bit cast since signed integers are uncommon to deal with
    i64 sx, sy;
    LIBMA_MEMCPY(&sx, x, sizeof(i64));
    LIBMA_MEMCPY(&sy, y, sizeof(i64));

    /* Arithmetic right shift fills with sign bit. */
    const i64 mask_x = sx >> 63;
    const i64 mask_y = sy >> 63;

    /* For negative values, flip the non-sign bits. */
    /* XOR with 0x7FFFFFFFFFFFFFFF when negative. */
    sx ^= (mask_x & (i64)DBL_ABS_MASK_U64);
    sy ^= (mask_y & (i64)DBL_ABS_MASK_U64);

    return sx <= sy;
}

int totalorderf(const float* x, const float* y) {
    // use manual bit cast since signed integers are uncommon to deal with
    i32 sx, sy;
    LIBMA_MEMCPY(&sx, x, sizeof(i32));
    LIBMA_MEMCPY(&sy, y, sizeof(i32));

    const i32 mask_x = sx >> 31;
    const i32 mask_y = sy >> 31;

    sx ^= (mask_x & (i32)FLT_ABS_MASK_U32);
    sy ^= (mask_y & (i32)FLT_ABS_MASK_U32);

    return sx <= sy;
}

int totalordermag(const double* x, const double* y) {
    u64 ux = f64_to_u64(*x);
    u64 uy = f64_to_u64(*y);

    /* Clear sign bits to get magnitudes. */
    ux &= DBL_ABS_MASK_U64;
    uy &= DBL_ABS_MASK_U64;

    /* Positive values: unsigned comparison is correct. */
    return ux <= uy;
}

int totalordermagf(const float* x, const float* y) {
    u64 ux = f32_to_u32(*x);
    u64 uy = f32_to_u32(*y);

    ux &= FLT_ABS_MASK_U32;
    uy &= FLT_ABS_MASK_U32;

    return ux <= uy;
}
