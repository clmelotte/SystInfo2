cmake_minimum_required(VERSION 3.15)
project(SystInfo2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SystInfo2
        lib_tar.c
        lib_tar.h
        tests.c)
