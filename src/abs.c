//
// Created by sammc on 1/21/26.
//
#include "libma.h"
#include "funcs/fabs.h"

// because fabsf and fabs are small functions and may be reused, they are placed in internal file to help inlining.

float fabsf(const float x) {
    return fabsf_impl(x);
}

double fabs(const double x) {
    return fabs_impl(x);
}
