//
// Created by sammc on 1/22/26.
//
#pragma once
#ifndef LIBMA_COPYSIGN_H
#define LIBMA_COPYSIGN_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "libma_def.h"
#include "bits/bitcasts.h"
#include "bits/extract.h"

KER_PURE_INLINE f32 copysignf_impl(const f32 x, const f32 y) {
    const u32 ux = f32_to_u32(x);
    const u32 uy = f32_to_u32(y);

    // 1. (ux & ~FLT_SIGN_MASK_U32) -> Keeps everything but the sign of 'x'
    // 2. (uy & FLT_SIGN_MASK_U32) -> Keeps only the sign bit of 'y'
    const u32 result = (ux & ~FLT_SIGN_MASK_U32) | (uy & FLT_SIGN_MASK_U32);

    return u32_to_f32(result);
}

KER_PURE_INLINE f64 copysign_impl(const f64 x, const f64 y) {
    const u64 ux = f64_to_u64(x);
    const u64 uy = f64_to_u64(y);

    // same as explanation above just uses constants adjusted for size
    const u64 result = (ux & ~DBL_SIGN_MASK_U64) | (uy & DBL_SIGN_MASK_U64);
    return u64_to_f64(result);
}

#endif //LIBMA_COPYSIGN_H
