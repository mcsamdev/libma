//
// Created by sammc on 1/21/26.
//
#pragma once
#ifndef LIBMA_LIBMA_DEF_H
#define LIBMA_LIBMA_DEF_H
/* NOTE: This is only for static assert detection, libma_float.h is preferred over float.h
 * The reason that we don't use libma_float.h here is that it just makes the constants assuming 64 bit.
 * float.h, on the other hand, comes with system and configuration information that can vary between platforms.
 */
#include <float.h>
#include <stdint.h>
#include <string.h>
#define LIBMA_INTERNAL

#define LIBMA_VERSION "0.1.0"
#define LIBMA_VERSION_MAJOR 0
#define LIBMA_VERSION_MINOR 1
#define LIBMA_VERSION_PATCH 0

/* ---- C99 static assert ---- */
#define LIBMA_JOIN2(a, b) a##b
#define LIBMA_JOIN(a, b) LIBMA_JOIN2(a, b)
#define LIBMA_STATIC_ASSERT(cond, name) typedef char LIBMA_JOIN(static_assert_, name)[(cond) ? 1 : -1]

/* ---- target requirements ---- */

/* 64-bit target (pointer size) */
LIBMA_STATIC_ASSERT(sizeof(void*) == 8, target_must_be_64bit);

/* Require radix-2 floats (IEEE-754 is base-2) */
LIBMA_STATIC_ASSERT(FLT_RADIX == 2, float_must_be_radix2);

/* binary32 checks */
LIBMA_STATIC_ASSERT(sizeof(float) == 4, float_must_be_32bit);
LIBMA_STATIC_ASSERT(FLT_MANT_DIG == 24, float_mantissa_must_be_24);
LIBMA_STATIC_ASSERT(FLT_MAX_EXP == 128, float_maxexp_must_be_128);
LIBMA_STATIC_ASSERT(FLT_MIN_EXP == -125, float_minexp_must_be_minus125);

/* binary64 checks */
LIBMA_STATIC_ASSERT(sizeof(double) == 8, double_must_be_64bit);
LIBMA_STATIC_ASSERT(DBL_MANT_DIG == 53, double_mantissa_must_be_53);
LIBMA_STATIC_ASSERT(DBL_MAX_EXP == 1024, double_maxexp_must_be_1024);
LIBMA_STATIC_ASSERT(DBL_MIN_EXP == -1021, double_minexp_must_be_minus1021);

// detect compiler
#if defined(__clang__)
#define CLANG 1
#elif defined(_MSC_VER)
#define MSVC 1
#elif defined(__GNUC__)
#define GCC 1
#else
#error "Unknown compiler"
#endif

#if defined(CLANG) || defined(GCC)
#define LIBMA_CLZ32(x) __builtin_clz(x)
#elif defined(MSVC)
#define LIBMA_CLZ32(x) __lzcnt(x)
#else
#define LIBMA_CLZ32(x) ({                     \
u32 _v = (u32)(x);              \
u32 _r;                              \
if (_v == 0) {                            \
_r = 32;                              \
} else {                                  \
_v |= _v >> 1;                        \
_v |= _v >> 2;                        \
_v |= _v >> 4;                        \
_v |= _v >> 8;                        \
_v |= _v >> 16;                       \
static const u8 _idx[32] = {     \
0,  9,  1, 10, 13, 21,  2, 29,     \
11, 14, 16, 18, 22, 25,  3, 30,     \
8, 12, 20, 28, 15, 17, 24,  7,     \
19, 27, 23,  6, 26,  5,  4, 31      \
};                                    \
u32 _msb =                       \
_idx[(u32)(_v * 0x07C4ACDDu) >> 27]; \
_r = 31u - _msb;                      \
}                                         \
_r;                                       \
})
#endif

#if defined(CLANG) || defined(GCC)
#define LIBMA_CLZ64(x) __builtin_clzll(x)
#elif defined(MSVC)
#define LIBMA_CLZ64(x) __lzcnt64(x)
#else
#define LIBMA_CLZ64(x) ({                         \
u64 _v = (u64)(x);                  \
u32 _r;                                  \
if (_v == 0) {                                \
_r = 64;                                  \
} else {                                      \
_v |= _v >> 1;                            \
_v |= _v >> 2;                            \
_v |= _v >> 4;                            \
_v |= _v >> 8;                            \
_v |= _v >> 16;                           \
_v |= _v >> 32;                           \
static const u8 _idx[64] = {         \
0,  1,  2,  7,  3, 13,  8, 19,         \
4, 25, 14, 28,  9, 34, 20, 40,         \
5, 17, 26, 38, 15, 46, 29, 48,         \
10, 31, 35, 54, 21, 50, 41, 57,         \
63,  6, 12, 18, 24, 27, 33, 39,         \
16, 37, 45, 47, 30, 53, 49, 56,         \
62, 11, 23, 32, 36, 44, 52, 55,         \
61, 22, 43, 51, 60, 42, 59, 58          \
};                                        \
u64 _msb =                           \
_idx[(uint64_t)(_v * 0x03F79D71B4CB0A89ULL) >> 58]; \
_r = 63u - (u32)_msb;                 \
}                                             \
_r;                                           \
})
#endif

#define KER_INLINE static inline

#if defined(CLANG) || defined(GCC)
#define KER_FORCE_INLINE static inline __attribute__((always_inline))
#elif defined(MSVC)
#define KER_FORCE_INLINE static __forceinline
#endif

/* ---- function attributes ---- */

#if defined(CLANG) || defined(GCC)
#define KER_ATTR_CONST __attribute__((const))
#define KER_ATTR_PURE __attribute__((pure))
#define KER_NOINLINE __attribute__((noinline))
#define KER_UNUSED __attribute__((unused))
#define KER_LIKELY(x) __builtin_expect(!!(x), 1)
#define KER_UNLIKELY(x) __builtin_expect(!!(x), 0)
#define KER_RESTRICT __restrict__
#elif defined(MSVC)
/* MSVC doesn't have GCC-style const/pure attributes */
#define KER_ATTR_CONST
#define KER_ATTR_PURE
#define KER_NOINLINE __declspec(noinline)
#define KER_UNUSED
#define KER_LIKELY(x) (x)
#define KER_UNLIKELY(x) (x)
#define KER_RESTRICT __restrict
#endif

/* Convenience wrappers if you like writing it as "KER_CONST_FN(double) foo(...)" */
#define KER_CONST_FN(ret_type) ret_type KER_ATTR_CONST
#define KER_PURE_FN(ret_type) ret_type KER_ATTR_PURE

#ifdef LIBMA_INTERNAL
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t bool;
#define TRUE 1
#define FALSE 0
// normalization, everything non 0 (false) collapses to 1 (true)
#define BOOL(x) ((x) ? TRUE : FALSE)

// these two can be used since checks above ensure 64 bit systems and correct semantics

typedef float f32;
typedef double f64;
#endif

#if defined(CLANG) || defined(GCC)
#define KER_CONST_INLINE static inline __attribute__((const, always_inline))
#elif defined(MSVC)
/* MSVC: no const-function equivalent */
#define KER_CONST_INLINE static __forceinline
#endif

#if defined(CLANG) || defined(GCC)
#define KER_PURE_INLINE static inline __attribute__((pure, always_inline))
#elif defined(MSVC)
#define KER_PURE_INLINE static __forceinline
#endif

/* Prefer compiler builtin memcpy when available */
#if defined(CLANG) || defined(GCC)
#define LIBMA_MEMCPY(dst, src, n) __builtin_memcpy((dst), (src), (n))
#else
#define LIBMA_MEMCPY(dst, src, n) memcpy((dst), (src), (n))
#endif

#define LIBMA_STATIC_ASSERT_SAME_SIZE(a, b, name) LIBMA_STATIC_ASSERT(sizeof(a) == sizeof(b), name)

#endif // LIBMA_LIBMA_DEF_H
