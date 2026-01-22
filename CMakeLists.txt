cmake_minimum_required(VERSION 4.1)
project(libma VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED)

add_executable(libma main.c
        include/libma.h
        include/libma_float.h)
