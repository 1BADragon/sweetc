cmake_minimum_required(VERSION 3.14)
project(sc_testing C)


set(LIB_SRCS
    src/test_harness.c)

add_library(sc_testing STATIC ${LIB_SRCS})
target_compile_options(sc_testing PRIVATE -Wall -Wextra)
target_include_directories(sc_testing PUBLIC include)
set_target_properties(sc_testing
    PROPERTIES
    C_STANDARD 11)
