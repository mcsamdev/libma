//
// Created by sammc on 1/2/26.
//
#include "libma.h"
#include "scalbn.h"

double scalbn(const double x, const int n) {
    return ker_dbl_scalbn(x, n);
}

float scalbnf(const float x, const int n) {
    return ker_flt_scalbn(x, n);
}

double ldexp(const double x, const int exp) {
    return ker_dbl_scalbn(x, exp);
}

float ldexpf(const float x, const int exp) {
    return ker_flt_scalbn(x, exp);
}

double frexp(const double x, int* restrict exp) {
    return ker_dbl_frexp(x, exp);
}

float frexpf(const float x, int* restrict exp) {
    return ker_flt_frexp(x, exp);
}

int ilogb(const double x) {
    return ker_dbl_ilogb(x);
}

int ilogbf(const float x) {
    return ker_flt_ilogb(x);
}

double logb(const double x) {
    return ker_dbl_logb(x);
}

float logbf(const float x) {
    return ker_flt_logb(x);
}
