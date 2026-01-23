//
// Created by sammc on 1/22/26.
//
#pragma once
#ifndef LIBMA_FABS_H
#define LIBMA_FABS_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "libma_def.h"
#include "bits/bitcasts.h"
#include "bits/consts.h"

KER_PURE_INLINE f32 fabsf_impl(const f32 f) {
    const u32 u = f32_to_u32(f);
    return u32_to_f32(u & ~FLT_SIGN_MASK_U32);
}

KER_PURE_INLINE f64 fabs_impl(const f64 f) {
    const u64 u = f64_to_u64(f);
    return u64_to_f64(u & ~DBL_SIGN_MASK_U64);
}
#endif //LIBMA_FABS_H
