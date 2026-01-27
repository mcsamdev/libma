//
// Created by sammc on 1/24/26.
//
#include "funcs/scalbn.h"
#include "libma.h"
#include "bits/bitcasts.h"
#include "bits/classify.h"
#include "funcs/normalize.h"

double scalbn(double x, int n) {
    if(n == 0) {
        return x;
    }
    const u64 ux = f64_to_u64(x);
    if(f64_is_nan_from_u64(ux) || f64_is_infinite_from_u64(ux)) {
        return x;
    }
    const u64 exp = f64_get_exp_from_u64(ux);
    if(exp == 0) {
        if(x == 0) {
            return x;
        }
        x *= 18014398509481984.0; // mul by 2^54
        n -= 54; // offset mul
        return scalbn_impl_f64(x, n);
    }
    return u64_to_f64(scalbn_impl_u64(ux, n));
}

float scalbnf(float x, int n) {
    if(n == 0) {
        return x;
    }
    const u32 ux = f32_to_u32(x);
    if(f32_is_nan_from_u32(ux) || f32_is_infinite_from_u32(ux)) {
        return x;
    }
    const u32 exp = f32_get_exp_from_u32(ux);
    if(exp == 0) {
        if(x == 0) {
            return x;
        }
        x *= 33554432.0f; // mul by 2^25
        n -= 25;
        return scalbn_impl_f32(x, n);
    }
    return u32_to_f32(scalbn_impl_u32(ux, n));
}

double ldexp(const double x, const int n) {
    return scalbn(x, n);
}

float ldexpf(const float x, const int n) {
    return scalbnf(x, n);
}

double scalbln(double x, long int n) {
    if(n == 0) {
        return x;
    }
    const u64 ux = f64_to_u64(x);
    if(f64_is_nan_from_u64(ux) || f64_is_infinite_from_u64(ux)) {
        return x;
    }
    const u64 exp = f64_get_exp_from_u64(ux);
    if(exp == 0) {
        if(x == 0) {
            return x;
        }
        x *= 18014398509481984.0; // mul by 2^54
        n -= 54; // offset mul
        return scalbln_impl_f64(x, n);
    }
    return u64_to_f64(scalbln_impl_u64(ux, n));
}

float scalblnf(float x, long int n) {
    if(n == 0) {
        return x;
    }
    const u32 ux = f32_to_u32(x);
    if(f32_is_nan_from_u32(ux) || f32_is_infinite_from_u32(ux)) {
        return x;
    }
    const u32 exp = f32_get_exp_from_u32(ux);
    if(exp == 0) {
        if(x == 0) {
            return x;
        }
        x *= 33554432.0f; // mul by 2^25
        n -= 25;
        return scalbln_impl_f32(x, n);
    }
    return u32_to_f32(scalbln_impl_u32(ux, n));
}
