//
// Created by sammc on 1/23/26.
//
#pragma once
#ifndef LIBMA_CLASSIFY_H
#define LIBMA_CLASSIFY_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "consts.h"
#include "extract.h"
#include "libma_def.h"

KER_CONST_INLINE bool f32_is_qnan_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) > FLT_EXP_MASK_U32 && (u & FLT_QNAN_BIT_U32));
}

KER_PURE_INLINE bool f32_is_qnan(const f32 x) {
    return f32_is_qnan_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_nan_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) > FLT_EXP_MASK_U32);
}

KER_PURE_INLINE bool f32_is_nan(const f32 x) {
    return f32_is_nan_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_infinite_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) == FLT_EXP_MASK_U32);
}

KER_PURE_INLINE bool f32_is_infinite(const f32 x) {
    return f32_is_infinite_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_pos_zero_from_u32(const u32 u) {
    return BOOL(u == FLT_POS_ZERO_U32);
}

KER_PURE_INLINE bool f32_is_pos_zero(const f32 x) {
    return f32_is_pos_zero_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_neg_zero_from_u32(const u32 u) {
    return BOOL(u == FLT_NEG_ZERO_U32);
}

KER_PURE_INLINE bool f32_is_neg_zero(const f32 x) {
    return f32_is_neg_zero_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_pos_inf_from_u32(const u32 u) {
    return BOOL(u == FLT_POS_INF_U32);
}

KER_PURE_INLINE bool f32_is_pos_inf(const f32 x) {
    return f32_is_pos_inf_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_neg_inf_from_u32(const u32 u) {
    return BOOL(u == FLT_NEG_INF_U32);
}

KER_PURE_INLINE bool f32_is_neg_inf(const f32 x) {
    return f32_is_neg_inf_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_pos_qnan_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) > FLT_EXP_MASK_U32 && (u & FLT_QNAN_BIT_U32) && !(u & FLT_SIGN_MASK_U32));
}

KER_PURE_INLINE bool f32_is_pos_qnan(const f32 x) {
    return f32_is_pos_qnan_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_neg_qnan_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) > FLT_EXP_MASK_U32 && (u & FLT_QNAN_BIT_U32) && (u & FLT_SIGN_MASK_U32));
}

KER_PURE_INLINE bool f32_is_neg_qnan(const f32 x) {
    return f32_is_neg_qnan_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_pos_snan_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) > FLT_EXP_MASK_U32 && !(u & FLT_QNAN_BIT_U32) && !(u & FLT_SIGN_MASK_U32));
}

KER_PURE_INLINE bool f32_is_pos_snan(const f32 x) {
    return f32_is_pos_snan_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_neg_snan_from_u32(const u32 u) {
    return BOOL((u & FLT_ABS_MASK_U32) > FLT_EXP_MASK_U32 && !(u & FLT_QNAN_BIT_U32) && (u & FLT_SIGN_MASK_U32));
}

KER_PURE_INLINE bool f32_is_neg_snan(const f32 x) {
    return f32_is_neg_snan_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f32_is_subnormal_from_u32(const u32 u) {
    // Subnormal: Exponent bits are 0, and Fraction bits are non-zero.
    // Optimized: (abs(u) - 1) < (minimum_normalized_abs_value - 1)
    // This effectively checks 0 < (u & ABS_MASK) < MIN_NORMAL
    return BOOL((u & FLT_ABS_MASK_U32) - 1u < FLT_EXP_MASK_U32 - 1u && !(u & FLT_EXP_MASK_U32));
}

KER_PURE_INLINE bool f32_is_subnormal(const f32 x) {
    return f32_is_subnormal_from_u32(f32_to_u32(x));
}

KER_CONST_INLINE bool f64_is_qnan_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) > DBL_EXP_MASK_U64 && (u & DBL_QNAN_BIT_U64));
}

KER_CONST_INLINE bool f64_is_nan_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) > DBL_EXP_MASK_U64);
}

KER_PURE_INLINE bool f64_is_nan(const f64 x) {
    return f64_is_nan_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_infinite_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) == DBL_EXP_MASK_U64);
}

KER_PURE_INLINE bool f64_is_infinite(const f64 x) {
    return f64_is_infinite_from_u64(f64_to_u64(x));
}

KER_PURE_INLINE bool f64_is_qnan(const f64 x) {
    return f64_is_qnan_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_pos_zero_from_u64(const u64 u) {
    return BOOL(u == DBL_POS_ZERO_U64);
}

KER_PURE_INLINE bool f64_is_pos_zero(const f64 x) {
    return f64_is_pos_zero_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_neg_zero_from_u64(const u64 u) {
    return BOOL(u == DBL_NEG_ZERO_U64);
}

KER_PURE_INLINE bool f64_is_neg_zero(const f64 x) {
    return f64_is_neg_zero_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_pos_inf_from_u64(const u64 u) {
    return BOOL(u == DBL_POS_INF_U64);
}

KER_PURE_INLINE bool f64_is_pos_inf(const f64 x) {
    return f64_is_pos_inf_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_neg_inf_from_u64(const u64 u) {
    return BOOL(u == DBL_NEG_INF_U64);
}

KER_PURE_INLINE bool f64_is_neg_inf(const f64 x) {
    return f64_is_neg_inf_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_pos_qnan_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) > DBL_EXP_MASK_U64 && (u & DBL_QNAN_BIT_U64) && !(u & DBL_SIGN_MASK_U64));
}

KER_PURE_INLINE bool f64_is_pos_qnan(const f64 x) {
    return f64_is_pos_qnan_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_neg_qnan_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) > DBL_EXP_MASK_U64 && (u & DBL_QNAN_BIT_U64) && (u & DBL_SIGN_MASK_U64));
}

KER_PURE_INLINE bool f64_is_neg_qnan(const f64 x) {
    return f64_is_neg_qnan_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_pos_snan_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) > DBL_EXP_MASK_U64 && !(u & DBL_QNAN_BIT_U64) && !(u & DBL_SIGN_MASK_U64));
}

KER_PURE_INLINE bool f64_is_pos_snan(const f64 x) {
    return f64_is_pos_snan_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_subnormal_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) - 1ULL < DBL_EXP_MASK_U64 - 1ULL && !(u & DBL_EXP_MASK_U64));
}

KER_PURE_INLINE bool f64_is_subnormal(const f64 x) {
    return f64_is_subnormal_from_u64(f64_to_u64(x));
}

KER_CONST_INLINE bool f64_is_neg_snan_from_u64(const u64 u) {
    return BOOL((u & DBL_ABS_MASK_U64) > DBL_EXP_MASK_U64 && !(u & DBL_QNAN_BIT_U64) && (u & DBL_SIGN_MASK_U64));
}

KER_PURE_INLINE bool f64_is_neg_snan(const f64 x) {
    return f64_is_neg_snan_from_u64(f64_to_u64(x));
}

#endif //LIBMA_CLASSIFY_H
