//
// Created by sammc on 1/26/26.
//
#pragma once
#ifndef LIBMA_NORMALIZE_H
#define LIBMA_NORMALIZE_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "libma_def.h"
#include "bits/bitcasts.h"
#include "bits/construct.h"
#include "bits/extract.h"

KER_CONST_INLINE u32 f32_normalize_from_u32(const u32 u) {
    const u32 sign = f32_get_sign_from_u32(u);
    u32 frac = f32_get_frac_from_u32(u);

    if(frac == 0) {
        return f32_construct_from_bits(sign, 0, 0);
    }

    // Shift left until the implicit bit would be at bit 23
    // LIBMA_CLZ32(frac) returns leading zeros in a 32-bit int.
    // frac is at most 23 bits, so there are at least 32-23 = 9 leading zeros.
    const int shift = LIBMA_CLZ32(frac) - 8;
    frac <<= shift;

    // The exponent becomes 1 - shift
    const i32 exp = 1 - shift;

    return f32_construct_from_bits(sign, (u32)exp, frac);
}

KER_CONST_INLINE u64 f64_normalize_from_u64(const u64 u) {
    const u64 sign = f64_get_sign_from_u64(u);
    u64 frac = f64_get_frac_from_u64(u);

    if(frac == 0) {
        return f64_construct_from_bits(sign, 0, 0);
    }

    const int shift = LIBMA_CLZ64(frac) - 11;
    frac <<= shift;
    const i32 exp = 1 - shift;

    return f64_construct_from_bits(sign, (u64)exp, frac);
}

KER_PURE_INLINE f32 normalize_f32_impl(const f32 f) {
    return u32_to_f32(f32_normalize_from_u32(f32_to_u32(f)));
}

KER_PURE_INLINE f64 normalize_f64_impl(const f64 f) {
    return u64_to_f64(f64_normalize_from_u64(f64_to_u64(f)));
}

#endif //LIBMA_NORMALIZE_H
