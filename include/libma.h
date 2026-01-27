
// Created by sammc on 1/21/26.
//
#pragma once
#ifndef LIBMA_LIBMA_H
#define LIBMA_LIBMA_H

#include <stdint.h>

#ifdef __cplusplus
#define RESTRICT
extern "C" {



#else
#define RESTRICT restrict
#endif

/* bit and classification stuff */
double fabs(double x);
float fabsf(float x);

double copysign(double x, double y);
float copysignf(float x, float y);

/* Total ordering stuff */
int totalorder(const double* x, const double* y);
int totalorderf(const float* x, const float* y);

int totalordermag(const double* x, const double* y);
int totalordermagf(const float* x, const float* y);

/* NaN construction */
double nan(const char* tagp);
float nanf(const char* tagp);

/* 1. exp manip and scaling */
double scalbn(double x, int n);
float scalbnf(float x, int n);

double ldexp(double x, int exp);
float ldexpf(float x, int exp);

double scalbln(double x, long int n);
float scalblnf(float x, long int n);

double frexp(double x, int* exp);
float frexpf(float x, int* exp);

int ilogb(double x);
int ilogbf(float x);

long int llogb(double x);
long int llogbf(float x);

double logb(double x);
float logbf(float x);

/* 2. adjacent / rounding primitives */
double nextafter(double x, double y);
float nextafterf(float x, float y);

double nextup(double x);
float nextupf(float x);

double nextdown(double x);
float nextdownf(float x);

double floor(double x);
float floorf(float x);

double ceil(double x);
float ceilf(float x);

double trunc(double x);
float truncf(float x);

double round(double x);
float roundf(float x);

double roundeven(double x);
float roundevenf(float x);

long lround(double x);
long lroundf(float x);

long long llround(double x);
long long llroundf(float x);

double rint(double x);
float rintf(float x);

long lrint(double x);
long lrintf(float x);

long long llrint(double x);
long long llrintf(float x);

double nearbyint(double x);
float nearbyintf(float x);

/* 3) Remainder / decomposition */
double modf(double x, double* iptr);
float modff(float x, float* iptr);

double fmod(double x, double y);
float fmodf(float x, float y);

double remainder(double x, double y);
float remainderf(float x, float y);

double remquo(double x, double y, int* quo);
float remquof(float x, float y, int* quo);

double fmax(double x, double y);
float fmaxf(float x, float y);

double fmin(double x, double y);
float fminf(float x, float y);

double fmaxmag(double x, double y);
float fmaxmagf(float x, float y);

double fminmag(double x, double y);
float fminmagf(float x, float y);

double fmaximum(double x, double y);
float fmaximumf(float x, float y);

double fminimum(double x, double y);
float fminimumf(float x, float y);

double fmaximum_mag(double x, double y);
float fmaximum_magf(float x, float y);

double fminimum_mag(double x, double y);
float fminimum_magf(float x, float y);

double fmaximum_num(double x, double y);
float fmaximum_numf(float x, float y);

double fminimum_num(double x, double y);
float fminimum_numf(float x, float y);

double fmaximum_mag_num(double x, double y);
float fmaximum_mag_numf(float x, float y);

double fminimum_mag_num(double x, double y);
float fminimum_mag_numf(float x, float y);

/* 5. core arithmetic helpers */
double fdim(double x, double y);
float fdimf(float x, float y);

double fma(double x, double y, double z);
float fmaf(float x, float y, float z);

/* Narrowing “round once” ops (C23 / TS 18661-1 merged) */
float fadd(double x, double y);
float fsub(double x, double y);
float fmul(double x, double y);
float fdiv(double x, double y);
float ffma(double x, double y, double z);
float fsqrt(double x);

/* 6. roots */
double sqrt(double x);
float sqrtf(float x);

double cbrt(double x);
float cbrtf(float x);

/* 7. Exponential / logarithmic */
double exp(double x);
float expf(float x);

double expm1(double x);
float expm1f(float x);

double exp2(double x);
float exp2f(float x);

double exp2m1(double x);
float exp2m1f(float x);

double exp10(double x);
float exp10f(float x);

double exp10m1(double x);
float exp10m1f(float x);

double log(double x);
float logf(float x);

double log1p(double x);
float log1pf(float x);

double logp1(double x);
float logp1f(float x);

double log2(double x);
float log2f(float x);

double log2p1(double x);
float log2p1f(float x);

double log10(double x);
float log10f(float x);

double log10p1(double x);
float log10p1f(float x);

/* 8. Power */
double pow(double x, double y);
float powf(float x, float y);

/* 9. root stuff */
double rsqrt(double x);
float rsqrtf(float x);

double rootn(double x, int n);
float rootnf(float x, int n);

double pown(double x, int n);
float pownf(float x, int n);

double powr(double x, double y);
float powrf(float x, float y);

double compound(double x, double y);
float compoundf(float x, float y);

double compoundn(double x, int n);
float compoundnf(float x, int n);

/* 10. Trigonometric */
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

/* pi-scaled */
double sinpi(double x);
float sinpif(float x);

double cospi(double x);
float cospif(float x);

double tanpi(double x);
float tanpif(float x);

double asinpi(double x);
float asinpif(float x);

double acospi(double x);
float acospif(float x);

double atanpi(double x);
float atanpif(float x);

double atan2pi(double y, double x);
float atan2pif(float y, float x);

/* 11. Hyperbolic */
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

/* 12. Derived / numerically sensitive helpers */
double hypot(double x, double y);
float hypotf(float x, float y);

/* 13. Error / gamma functions */
double erf(double x);
float erff(float x);

double erfc(double x);
float erfcf(float x);

double tgamma(double x);
float tgammaf(float x);

double lgamma(double x);
float lgammaf(float x);

/* 14. fromfp */
intmax_t fromfp(double x, int round, unsigned int width);
intmax_t fromfpf(float x, int round, unsigned int width);

intmax_t fromfpx(double x, int round, unsigned int width);
intmax_t fromfpxf(float x, int round, unsigned int width);

uintmax_t ufromfp(double x, int round, unsigned int width);
uintmax_t ufromfpf(float x, int round, unsigned int width);

uintmax_t ufromfpx(double x, int round, unsigned int width);
uintmax_t ufromfpxf(float x, int round, unsigned int width);

#ifdef __cplusplus
}
#endif

#endif // LIBMA_LIBMA_H
