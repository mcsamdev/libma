//
// Created by sammc on 1/24/26.
//
#pragma once
#ifndef LIBMA_SCALBN_H
#define LIBMA_SCALBN_H
#ifndef LIBMA_INTERNAL
#define LIBMA_INTERNAL
#endif
#include "libma_def.h"
#include "bits/construct.h"
#include "bits/extract.h"

KER_CONST_INLINE u64 scalbn_impl_u64(const u64 x, const int n) {
    const u64 sign = f64_get_sign_from_u64(x);
    const u64 frac = f64_get_frac_from_u64(x);
    // dont have to use unbiased exp since (stored_exp - bias + n) + bias == stored_exp + n
    // also must cast to i32 to allow for negative n
    i32 exp = (i32)f64_get_exp_from_u64(x);
    exp += n;
    return f64_construct_from_bits(sign, (u64)exp, frac);
}

KER_CONST_INLINE u32 scalbn_impl_u32(const u32 x, const int n) {
    const u32 sign = f32_get_sign_from_u32(x);
    const u32 frac = f32_get_frac_from_u32(x);
    i32 exp = (i32)f32_get_exp_from_u32(x);
    exp += n;
    return f32_construct_from_bits(sign, (u32)exp, frac);
}

KER_CONST_INLINE u64 scalbln_impl_u64(const u64 x, const long int n) {
    const u64 sign = f64_get_sign_from_u64(x);
    const u64 frac = f64_get_frac_from_u64(x);
    i64 exp = (i64)f64_get_exp_from_u64(x);
    exp += n;
    return f64_construct_from_bits(sign, (u64)exp, frac);
}

KER_CONST_INLINE u32 scalbln_impl_u32(const u32 x, const long int n) {
    const u32 sign = f32_get_sign_from_u32(x);
    const u32 frac = f32_get_frac_from_u32(x);
    i64 exp = (i64)f32_get_exp_from_u32(x);
    exp += n;
    return f32_construct_from_bits(sign, (u32)exp, frac);
}

KER_PURE_INLINE f64 scalbn_impl_f64(const f64 x, const int n) {
    const u64 ux = f64_to_u64(x);
    const u64 result = scalbn_impl_u64(ux, n);
    return u64_to_f64(result);
}

KER_PURE_INLINE f32 scalbn_impl_f32(const f32 x, const int n) {
    const u32 ux = f32_to_u32(x);
    const u32 result = scalbn_impl_u32(ux, n);
    return u32_to_f32(result);
}

KER_PURE_INLINE f64 scalbln_impl_f64(const f64 x, const long int n) {
    const u64 ux = f64_to_u64(x);
    const u64 result = scalbln_impl_u64(ux, n);
    return u64_to_f64(result);
}

KER_PURE_INLINE f32 scalbln_impl_f32(const f32 x, const long int n) {
    const u32 ux = f32_to_u32(x);
    const u32 result = scalbln_impl_u32(ux, n);
    return u32_to_f32(result);
}

#endif //LIBMA_SCALBN_H
