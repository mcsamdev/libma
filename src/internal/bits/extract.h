//
// Created by sammc on 1/21/26.
//
#pragma once
#ifndef LIBMA_EXTRACT_H
#define LIBMA_EXTRACT_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "bitcasts.h"
#include "consts.h"
#include "libma_def.h"

KER_CONST_INLINE u32 f32_get_sign_from_u32(const u32 u) {
    return (u & FLT_SIGN_MASK_U32) >> FLT_SIGN_SHIFT_U32;
}

KER_CONST_INLINE u32 f32_get_exp_from_u32(const u32 u) {
    return (u & FLT_EXP_MASK_U32) >> FLT_EXP_SHIFT_U32;
}

KER_CONST_INLINE u32 f32_get_frac_from_u32(const u32 u) {
    return (u & FLT_FRAC_MASK_U32) >> FLT_FRAC_SHIFT_U32;
}

KER_CONST_INLINE i32 f32_get_unbiased_exp_from_u32(const u32 u) {
    return (i32)f32_get_exp_from_u32(u) - (i32)FLT_EXP_BIAS_U32;
}

KER_PURE_INLINE u32 f32_get_sign_u32(const f32 f) {
    return f32_get_sign_from_u32(f32_to_u32(f));
}

KER_PURE_INLINE u32 f32_get_exp_u32(const f32 f) {
    return f32_get_exp_from_u32(f32_to_u32(f));
}

KER_PURE_INLINE u32 f32_get_frac_u32(const f32 f) {
    return f32_get_frac_from_u32(f32_to_u32(f));
}

KER_PURE_INLINE i32 f32_get_unbiased_exp_i32(const f32 f) {
    return f32_get_unbiased_exp_from_u32(f32_to_u32(f));
}

KER_CONST_INLINE u64 f64_get_sign_from_u64(const u64 u) {
    return (u & DBL_SIGN_MASK_U64) >> DBL_SIGN_SHIFT_U64;
}

KER_CONST_INLINE u64 f64_get_exp_from_u64(const u64 u) {
    return (u & DBL_EXP_MASK_U64) >> DBL_EXP_SHIFT_U64;
}

KER_CONST_INLINE u64 f64_get_frac_from_u64(const u64 u) {
    return (u & DBL_FRAC_MASK_U64) >> DBL_FRAC_SHIFT_U64;
}

KER_CONST_INLINE i32 f64_get_unbiased_exp_from_u64(const u64 u) {
    return (i32)f64_get_exp_from_u64(u) - (i32)DBL_EXP_BIAS_U64;
}

KER_PURE_INLINE u64 f64_get_sign_u64(const f64 f) {
    return f64_get_sign_from_u64(f64_to_u64(f));
}

KER_PURE_INLINE u64 f64_get_exp_u64(const f64 f) {
    return f64_get_exp_from_u64(f64_to_u64(f));
}

KER_PURE_INLINE u64 f64_get_frac_u64(const f64 f) {
    return f64_get_frac_from_u64(f64_to_u64(f));
}

KER_PURE_INLINE i32 f64_get_unbiased_exp_i32(const f64 f) {
    return f64_get_unbiased_exp_from_u64(f64_to_u64(f));
}

#endif // LIBMA_EXTRACT_H
