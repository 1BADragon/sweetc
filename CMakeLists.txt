cmake_minimum_required(VERSION 3.14)
project(sweetc C)

option(BUILD_TESTS "Builds project test apps" OFF)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    option(LINK_ASAN "Link in address sanatizer" ON)
else()
    option(LINK_ASAN "Link in address sanatizer" OFF)
endif()

set(LIB_SRCS
    src/dummy.c)

add_library(sweetc ${LIB_SRCS})
target_include_directories(sweetc
        PUBLIC include
)
set_target_properties(sweetc
    PROPERTIES
    C_STANDARD 11
)

if (LINK_ASAN)
    target_compile_options(sweetc PUBLIC -fsanitize=address)
    target_link_libraries(sweetc PUBLIC asan)
endif()

option(BUILD_TESTING "Build testing framework" ON)

if(BUILD_TESTING OR BUILD_TESTS OR "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_subdirectory(src/testing)
endif()

if (BUILD_TESTS OR "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    enable_testing()
    add_subdirectory(tests)
endif()
