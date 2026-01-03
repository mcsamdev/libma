#pragma once
#ifndef LIBMA_LIBRARY_H
#define LIBMA_LIBRARY_H

// 0. Classification / basic utilities

double fabs(double x);
float fabsf(float x);

double copysign(double x, double y);
float copysignf(float x, float y);

double fmax(double x, double y);
float fmaxf(float x, float y);

double fmin(double x, double y);
float fminf(float x, float y);

// 1. Exponent manipulation / scaling

double scalbn(double x, int n);
float scalbnf(float x, int n);

double ldexp(double x, int exp);
float ldexpf(float x, int exp);

double frexp(double x, int* exp);
float frexpf(float x, int* exp);

int ilogb(double x);
int ilogbf(float x);

double logb(double x);
float logbf(float x);

// 2. Adjacent / rounding primitives

double nextafter(double x, double y);
float nextafterf(float x, float y);

double floor(double x);
float floorf(float x);

double ceil(double x);
float ceilf(float x);

double trunc(double x);
float truncf(float x);

double round(double x);
float roundf(float x);

long lround(double x);
long lroundf(float x);

long long llround(double x);
long long llroundf(float x);

double rint(double x);
float rintf(float x);

double nearbyint(double x);
float nearbyintf(float x);

// 3. Remainder / decomposition

double modf(double x, double* iptr);
float modff(float x, float* iptr);

double fmod(double x, double y);
float fmodf(float x, float y);

double remainder(double x, double y);
float remainderf(float x, float y);

double remquo(double x, double y, int* quo);
float remquof(float x, float y, int* quo);


// 4. Core roots

double sqrt(double x);
float sqrtf(float x);

double cbrt(double x);
float cbrtf(float x);

// 5. Exponential / logarithmic core

double exp(double x);
float expf(float x);

double expm1(double x);
float expm1f(float x);

double log(double x);
float logf(float x);

double log1p(double x);
float log1pf(float x);

double log2(double x);
float log2f(float x);

double log10(double x);
float log10f(float x);

double exp2(double x);
float exp2f(float x);

// 6. Power

double pow(double x, double y);
float powf(float x, float y);

// 7. Trigonometric

double sin(double x);
float sinf(float x);

double cos(double x);
float cosf(float x);

double tan(double x);
float tanf(float x);

double asin(double x);
float asinf(float x);

double acos(double x);
float acosf(float x);

double atan(double x);
float atanf(float x);

double atan2(double y, double x);
float atan2f(float y, float x);

// 8. Hyperbolic

double sinh(double x);
float sinhf(float x);

double cosh(double x);
float coshf(float x);

double tanh(double x);
float tanhf(float x);

double asinh(double x);
float asinhf(float x);

double acosh(double x);
float acoshf(float x);

double atanh(double x);
float atanhf(float x);

// 9. Derived / numerically sensitive helpers

double hypot(double x, double y);
float hypotf(float x, float y);

// 10. Error / gamma functions (last)

double erf(double x);
float erff(float x);

double erfc(double x);
float erfcf(float x);

double tgamma(double x);
float tgammaf(float x);

double lgamma(double x);
float lgammaf(float x);
#endif // LIBMA_LIBRARY_H
