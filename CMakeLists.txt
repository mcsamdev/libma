cmake_minimum_required(VERSION 4.1)
project(libma VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED)

set(RELEASE_CFLAGS
        -O3 -march=native -funroll-loops -fno-strict-aliasing
)
set(DEBUG_CFLAGS
        -Og -g
        -Wall -Wextra -Wpedantic
        -Wshadow -Wcast-align -Wconversion -Wsign-conversion -Wfloat-equal
        -Wpointer-arith -Wundef -Wlogical-op -Wformat=2
)

add_library(libma STATIC
        include/libma.h
        include/libma_float.h
        src/abs.c
        src/internal/libma_def.h
        src/internal/bits/bitcasts.h
        src/internal/bits/extract.h
        src/internal/bits/consts.h
        src/internal/funcs/fabs.h)

target_include_directories(libma PUBLIC include)
target_include_directories(libma PRIVATE src/internal)


include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_supported OUTPUT error)
if (ipo_supported)
    set_target_properties(libma PROPERTIES INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif ()

# Apply flags by configuration
target_compile_options(libma PRIVATE
        $<$<CONFIG:Release>:${RELEASE_CFLAGS}>
        $<$<CONFIG:Debug>:${DEBUG_CFLAGS}>
)

# Apply macros by configuration
target_compile_definitions(libma PRIVATE
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Debug>:DEBUG>
)

# LTO: -flto often needs to be on the link step too
target_link_options(libma PRIVATE
        $<$<CONFIG:Release>:-flto>
)

