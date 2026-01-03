#pragma once
#ifndef LIBMA_LIBRARY_H
#define LIBMA_LIBRARY_H

// 0. Classification / basic utilities

/**
 * @brief Computes the absolute value of a double-precision floating-point number.
 *
 * This function returns the absolute value of the input double.
 * If the input is negative, the result is its positive counterpart;
 * otherwise, the number is returned as is.
 *
 * @param x The input number whose absolute value is to be computed.
 * @return The absolute value of the input number.
 */
double fabs(double x);
/**
 * @brief Computes the absolute value of a single-precision floating-point number.
 *
 * This function returns the absolute value of the input float.
 * If the input is negative, the result is its positive counterpart;
 * otherwise, the number is returned as is.
 *
 * @param x The input number whose absolute value is to be computed.
 * @return The absolute value of the input number.
 */
float fabsf(float x);
/**
 * @brief Returns a double-precision floating-point number with the magnitude of the first argument
 * and the sign of the second argument.
 *
 * This function combines the magnitude of the input number `x` with the sign of the input number `y`.
 * The result will have the absolute value of `x` but the sign of `y`. If `y` is positive or zero, the result
 * will also be positive, otherwise it will be negative.
 *
 * @param x The input number whose magnitude is to be used.
 * @param y The input number whose sign is to be used.
 * @return A double-precision floating-point number with the magnitude of `x` and the sign of `y`.
 */
double copysign(double x, double y);
/**
 * @brief Returns a floating-point number with the magnitude of one value and the sign of another.
 *
 * This function combines the magnitude of the first input argument (x) with the sign
 * of the second input argument (y). If y is positive, the result will have a positive sign;
 * if y is negative, the result will have a negative sign. The magnitude of the result corresponds
 * to the absolute value of x.
 *
 * @param x The input number whose magnitude is to be used.
 * @param y The input number whose sign is to be used.
 * @return A floating-point number with the magnitude of x and the sign of y.
 */
float copysignf(float x, float y);
/**
 * @brief Returns the maximum of two double-precision floating-point numbers.
 *
 * This function compares two double-precision floating-point numbers and
 * returns the greater of the two. If either input is a NaN, the function
 * returns the other non-NaN value. If both inputs are NaN, the behavior
 * is unspecified. Additionally, it handles the special case of signed zeros,
 * where +0.0 is considered greater than -0.0.
 *
 * @param x The first double-precision floating-point number.
 * @param y The second double-precision floating-point number.
 * @return The greater of the two input values, or the non-NaN value
 *         if one of the inputs is NaN.
 */
double fmax(double x, double y);
/**
 * @brief Returns the larger of two floating-point numbers.
 *
 * This function computes the maximum of two float values, taking into
 * consideration special cases such as NaN propagation and signed zero.
 * If either value is NaN, the other value is returned. If both values
 * are signed zeros, the result is the one with a positive sign.
 *
 * @param x The first float value to compare.
 * @param y The second float value to compare.
 * @return The greater of the two input float values. If either input
 *         is NaN, the other value is returned.
 */
float fmaxf(float x, float y);

/**
 * @brief Computes the smaller of two double-precision floating-point numbers.
 *
 * This function determines the smaller value between two double-precision
 * floating-point numbers. If one of the inputs is NaN (Not a Number),
 * the function returns the other value. If both inputs are zeros of
 * opposite signs, the function returns the negative zero. Otherwise,
 * it returns the lesser of the two input values.
 *
 * @param x The first double-precision floating-point number.
 * @param y The second double-precision floating-point number.
 * @return The smaller of the two input numbers, subject to special
 *         handling of NaN and signed zero cases.
 */
double fmin(double x, double y);
/**
 * @brief Determines the smaller of two single-precision floating-point numbers.
 *
 * This function compares the two input values and returns the smaller one.
 * If either input is NaN, the other value is returned. In the case where
 * both values are zero, the result depends on the sign of the zero values.
 *
 * @param x The first single-precision floating-point number to compare.
 * @param y The second single-precision floating-point number to compare.
 * @return The smaller of the two input values, or the non-NaN value if one input is NaN.
 */
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
