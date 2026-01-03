//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_POLY_H
#define LIBMA_POLY_H

#include "math_config.h"

// Horner poly helpers for both float and double.

/* float */
/**
 * Evaluates a first-degree polynomial (linear function) of the form c0 + c1 * x.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_poly1f(const float x, const float c0, const float c1) {
    return c0 + x * c1;
}

/**
 * Evaluates a second-degree polynomial (quadratic function) of the form c0 + c1 * x + c2 * x^2.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_poly2f(const float x, const float c0, const float c1, const float c2) {
    return (c2 * x + c1) * x + c0;
}

/**
 * Evaluates a third-degree polynomial of the form c0 + c1 * x + c2 * x^2 + c3 * x^3.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient of the constant term.
 * @param c1 The coefficient of the linear term.
 * @param c2 The coefficient of the quadratic term.
 * @param c3 The coefficient of the cubic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_poly3f(const float x,
                                            const float c0,
                                            const float c1,
                                            const float c2,
                                            const float c3) {
    return ((c3 * x + c2) * x + c1) * x + c0;
}

/**
 * Evaluates a fourth-degree polynomial of the form c0 + c1 * x + c2 * x^2 + c3 * x^3 + c4 * x^4.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @param c3 The coefficient for the cubic term.
 * @param c4 The coefficient for the quartic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_poly4f(const float x,
                                            const float c0,
                                            const float c1,
                                            const float c2,
                                            const float c3,
                                            const float c4) {
    return (((c4 * x + c3) * x + c2) * x + c1) * x + c0;
}

/**
 * Evaluates a fifth-degree polynomial of the form c0 + c1 * x + c2 * x^2 + c3 * x^3 + c4 * x^4 + c5 * x^5.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @param c3 The coefficient for the cubic term.
 * @param c4 The coefficient for the quartic term.
 * @param c5 The coefficient for the quintic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC float ker_poly5f(const float x,
                                            const float c0,
                                            const float c1,
                                            const float c2,
                                            const float c3,
                                            const float c4,
                                            const float c5) {
    return ((((c5 * x + c4) * x + c3) * x + c2) * x + c1) * x + c0;
}

/* double */
/**
 * Computes a first-degree polynomial given by the expression c0 + c1 * x.
 *
 * @param x The variable of the polynomial.
 * @param c0 The constant term coefficient.
 * @param c1 The linear term coefficient.
 * @return The result of the polynomial evaluation for the provided inputs.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_poly1(const double x, const double c0, const double c1) {
    return c0 + x * c1;
}

/**
 * Evaluates a second-degree polynomial (quadratic function) of the form c0 + c1 * x + c2 * x^2.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_poly2(const double x, const double c0, const double c1, const double c2) {
    return (c2 * x + c1) * x + c0;
}

/**
 * Evaluates a third-degree polynomial of the form c0 + c1 * x + c2 * x^2 + c3 * x^3.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @param c3 The coefficient for the cubic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_poly3(const double x,
                                            const double c0,
                                            const double c1,
                                            const double c2,
                                            const double c3) {
    return ((c3 * x + c2) * x + c1) * x + c0;
}

/**
 * Evaluates a fourth-degree polynomial of the form c0 + c1 * x + c2 * x^2 + c3 * x^3 + c4 * x^4.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @param c3 The coefficient for the cubic term.
 * @param c4 The coefficient for the quartic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_poly4(const double x,
                                            const double c0,
                                            const double c1,
                                            const double c2,
                                            const double c3,
                                            const double c4) {
    return (((c4 * x + c3) * x + c2) * x + c1) * x + c0;
}

/**
 * Evaluates a fifth-degree polynomial of the form c0 + c1 * x + c2 * x^2 + c3 * x^3 + c4 * x^4 + c5 * x^5.
 *
 * @param x The independent variable of the polynomial.
 * @param c0 The coefficient for the constant term.
 * @param c1 The coefficient for the linear term.
 * @param c2 The coefficient for the quadratic term.
 * @param c3 The coefficient for the cubic term.
 * @param c4 The coefficient for the quartic term.
 * @param c5 The coefficient for the quintic term.
 * @return The evaluated value of the polynomial at the given x.
 */
LIBMA_ALWAYS_INLINE_STATIC double ker_poly5(const double x,
                                            const double c0,
                                            const double c1,
                                            const double c2,
                                            const double c3,
                                            const double c4,
                                            const double c5) {
    return ((((c5 * x + c4) * x + c3) * x + c2) * x + c1) * x + c0;
}

#endif //LIBMA_POLY_H
