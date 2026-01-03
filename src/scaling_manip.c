//
// Created by sammc on 1/2/26.
//
#include "libma.h"
#include "scalbn.h"

double scalbn(const double x, int n) {
    return ker_dbl_scalbn(x, n);
}

float scalbnf(const float x, int n) {
    return ker_flt_scalbn(x, n);
}
