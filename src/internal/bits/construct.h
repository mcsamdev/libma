//
// Created by sammc on 1/24/26.
//
#pragma once
#ifndef LIBMA_CONSTRUCT_H
#define LIBMA_CONSTRUCT_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "consts.h"
#include "libma_def.h"

KER_CONST_INLINE u32 f32_construct_from_bits(const u32 sign, const u32 exp, const u32 frac) {
    return ((sign & 0x1u) << FLT_SIGN_SHIFT_U32) |
           ((exp & FLT_EXP_ALL_ONES_U32) << FLT_EXP_SHIFT_U32) |
           (frac & FLT_FRAC_MASK_U32);
}

KER_CONST_INLINE u64 f64_construct_from_bits(const u64 sign, const u64 exp, const u64 frac) {
    return ((sign & 0x1u) << DBL_SIGN_SHIFT_U64) |
           ((exp & DBL_EXP_ALL_ONES_U64) << DBL_EXP_SHIFT_U64) |
           (frac & DBL_FRAC_MASK_U64);
}
#endif //LIBMA_CONSTRUCT_H
