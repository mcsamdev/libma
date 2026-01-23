//
// Created by sammc on 1/22/26.
//
#include "funcs/copysign.h"
#include "libma.h"

float copysignf(const f32 x, const f32 y) {
    return copysignf_impl(x, y);
}

double copysign(const f64 x, const f64 y) {
    return copysign_impl(x, y);
}
