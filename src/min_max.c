//
// Created by sammc on 1/2/26.
//
#include "fp_classify.h"
#include "libma.h"

double copysign(const double x, const double y) {
    return ker_dbl_copysign(x, y);
}

float copysignf(const float x, const float y) {
    return ker_flt_copysign(x, y);
}

double fmax(const double x, const double y) {
    const uint64_t ux = ker_dbl_to_u64(x);
    const uint64_t uy = ker_dbl_to_u64(y);

    // IEEE 754-2019 Requirement: If either input is NaN, return a NaN.
    // This makes the operation associative and consistent.
    if(ker_dbl_isnan_u64(ux)) {
        return x; // Returns the NaN in x
    }
    if(ker_dbl_isnan_u64(uy)) {
        return y; // Returns the NaN in y
    }

    // Handle signed zeros: +0.0 is greater than -0.0
    if(x == 0.0 && y == 0.0) {
        return ker_dbl_sign_u64(ux) == 0 ? x : y;
    }

    return x > y ? x : y;
}

float fmaxf(const float x, const float y) {
    const uint32_t ux = ker_flt_to_u32(x);
    const uint32_t uy = ker_flt_to_u32(y);

    // NaN Propagation: If x or y is NaN, the result is NaN.
    if(ker_flt_isnan_u32(ux)) {
        return x;
    }
    if(ker_flt_isnan_u32(uy)) {
        return y;
    }

    if(x == 0.0f && y == 0.0f) {
        return ker_flt_sign_u32(ux) == 0 ? x : y;
    }

    return x > y ? x : y;
}

double fmin(const double x, const double y) {
    const uint64_t ux = ker_dbl_to_u64(x);
    const uint64_t uy = ker_dbl_to_u64(y);

    // IEEE 754-2019 'minimum' Requirement: Propagate NaNs.
    // If either x or y is NaN, return the NaN.
    if(ker_dbl_isnan_u64(ux)) {
        return x;
    }
    if(ker_dbl_isnan_u64(uy)) {
        return y;
    }

    // Handle signed zeros: -0.0 is strictly less than +0.0
    if(x == 0.0 && y == 0.0) {
        // Return x if it is negative zero, otherwise return y
        return ker_dbl_sign_u64(ux) != 0 ? x : y;
    }

    return x < y ? x : y;
}

float fminf(const float x, const float y) {
    const uint32_t ux = ker_flt_to_u32(x);
    const uint32_t uy = ker_flt_to_u32(y);

    // Propagation: NaN in, NaN out.
    if(ker_flt_isnan_u32(ux)) {
        return x;
    }
    if(ker_flt_isnan_u32(uy)) {
        return y;
    }

    if(x == 0.0f && y == 0.0f) {
        return ker_flt_sign_u32(ux) != 0 ? x : y;
    }

    return x < y ? x : y;
}
