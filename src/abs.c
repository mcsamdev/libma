//
// Created by sammc on 1/21/26.
//
#include "libma.h"
#include "funcs/fabs.h"

float fabsf(const float x) {
    return fabsf_impl(x);
}

double fabs(const double x) {
    return fabs_impl(x);
}
