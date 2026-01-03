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

    if(ker_dbl_isnan_u64(ux)) {
        return y;
    }
    if(ker_dbl_isnan_u64(uy)) {
        return x;
    }

    /* Handle signed zeros: +0.0 > -0.0
     * In IEEE-754 bit pattern, +0.0 is 0x0... and -0.0 is 0x8...
     * However, for comparison, we can use the actual floats. */
    if(x == 0.0 && y == 0.0) {
        return ker_dbl_sign_u64(ux) == 0 ? x : y;
    }

    return x > y ? x : y;
}

float fmaxf(const float x, const float y) {
    const uint32_t ux = ker_flt_to_u32(x);
    const uint32_t uy = ker_flt_to_u32(y);

    if(ker_flt_isnan_u32(ux)) {
        return y;
    }
    if(ker_flt_isnan_u32(uy)) {
        return x;
    }

    if(x == 0.0f && y == 0.0f) {
        return ker_flt_sign_u32(ux) == 0 ? x : y;
    }

    return x > y ? x : y;
}

double fmin(const double x, const double y) {
    const uint64_t ux = ker_dbl_to_u64(x);
    const uint64_t uy = ker_dbl_to_u64(y);

    if(ker_dbl_isnan_u64(ux)) {
        return y;
    }
    if(ker_dbl_isnan_u64(uy)) {
        return x;
    }

    if(x == 0.0 && y == 0.0) {
        return ker_dbl_sign_u64(ux) != 0 ? x : y;
    }

    return x < y ? x : y;
}

float fminf(const float x, const float y) {
    const uint32_t ux = ker_flt_to_u32(x);
    const uint32_t uy = ker_flt_to_u32(y);

    if(ker_flt_isnan_u32(ux)) {
        return y;
    }
    if(ker_flt_isnan_u32(uy)) {
        return x;
    }

    if(x == 0.0f && y == 0.0f) {
        return ker_flt_sign_u32(ux) != 0 ? x : y;
    }

    return x < y ? x : y;
}
