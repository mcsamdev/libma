cmake_minimum_required(VERSION 4.1)
project(libma VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED true)


add_library(libma STATIC
        src/internal/bits.h
        src/internal/math_config.h
        src/internal/fp_classify.h
        src/internal/poly.h
        src/internal/special.h
        src/internal/normalize.h
        src/internal/mantissa.h
        src/internal/scalbn.h
        src/internal/from_mantissa.h)

target_include_directories(libma PUBLIC libma.h)
target_include_directories(libma PRIVATE src/internal)

