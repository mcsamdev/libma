//
// Created by sammc on 1/2/26.
//
#pragma once
#ifndef LIBMA_MATH_CONFIG_H
#define LIBMA_MATH_CONFIG_H

#include <float.h>
#include <limits.h>
#include <stdint.h>

/* --- baseline assumptions --- */
#if CHAR_BIT != 8
#  error "Requires 8-bit bytes"
#endif

/* IEEE-754 binary32/binary64 checks */
_Static_assert(sizeof(float) == 4, "requires 32-bit float");
_Static_assert(sizeof(double) == 8, "requires 64-bit double");

_Static_assert(FLT_MANT_DIG == 24, "requires IEEE-754 binary32");
_Static_assert(FLT_MAX_EXP == 128, "requires IEEE-754 binary32");

_Static_assert(DBL_MANT_DIG == 53, "requires IEEE-754 binary64");
_Static_assert(DBL_MAX_EXP == 1024, "requires IEEE-754 binary64");

/* --- compiler detection --- */
#if defined(__clang__)
#  define LIBMA_CLANG 1
#else
#  define LIBMA_CLANG 0
#endif

#if defined(__GNUC__) && !defined(__clang__)
#  define LIBMA_GCC 1
#else
#  define LIBMA_GCC 0
#endif

#if defined(_MSC_VER)
#  define LIBMA_MSVC 1
#else
#  define LIBMA_MSVC 0
#endif

/* --- arch detection (optional micro-opts) --- */
#if defined(__x86_64__) || defined(_M_X64)
#  define LIBMA_X86_64 1
#else
#  define LIBMA_X86_64 0
#endif

#if defined(__aarch64__) || defined(_M_ARM64)
#  define LIBMA_AARCH64 1
#else
#  define LIBMA_AARCH64 0
#endif

/* --- force-inline --- */
#if LIBMA_GCC || LIBMA_CLANG
#  define LIBMA_ALWAYS_INLINE_STATIC static inline __attribute__((always_inline))
#  define LIBMA_ALWAYS_INLINE inline __attribute__((always_inline))
#elif LIBMA_MSVC
#  define LIBMA_ALWAYS_INLINE_STATIC static inline __forceinline
#  define LIBMA_ALWAYS_INLINE inline __forceinline
#else
#  define LIBMA_ALWAYS_INLINE_STATIC static inline
#  define LIBMA_ALWAYS_INLINE inline
#endif

/* --- builtin helpers --- */
#if LIBMA_GCC || LIBMA_CLANG
#  define LIBMA_BUILTIN_MEMCPY 1
#else
#  define LIBMA_BUILTIN_MEMCPY 0
#endif

/* --- math constants --- */
#define LIBMA_FP_ILOGB0    INT_MIN
#define LIBMA_FP_ILOGBNAN  INT_MAX

#endif //LIBMA_MATH_CONFIG_H
