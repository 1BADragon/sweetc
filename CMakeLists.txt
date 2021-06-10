cmake_minimum_required(VERSION 3.14)
project(sweetc C)

option(BUILD_TESTS "Builds project test apps" OFF)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    option(LINK_ASAN "Link in address sanatizer" ON)
else()
    option(LINK_ASAN "Link in address sanatizer" OFF)
endif()

add_library(sweetc "")
target_compile_options(sweetc PRIVATE -Wall -Wextra -Wbad-function-cast -Wformat=2
    -Wmissing-include-dirs -Wmissing-declarations -Wmissing-prototypes -Wsequence-point
    -Wshadow -Wstrict-prototypes -Wunreachable-code -Wunused-but-set-parameter
    -Wwrite-strings)
target_include_directories(sweetc
        PUBLIC include
)
set_target_properties(sweetc
    PROPERTIES
    C_STANDARD 11
)

add_subdirectory(src)

if (LINK_ASAN)
    target_compile_options(sweetc PUBLIC -fsanitize=address)
    target_link_libraries(sweetc PUBLIC asan)
endif()

option(BUILD_TESTING "Build testing framework" ON)

if(BUILD_TESTING OR BUILD_TESTS OR "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_compile_options(sweetc PUBLIC -fprofile-arcs -ftest-coverage)
    target_link_options(sweetc PUBLIC -fprofile-arcs -ftest-coverage)

    add_custom_target(coverage
        COMMAND gcovr -r ${PROJECT_SOURCE_DIR}/src --object-directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/sweetc.dir/src/
        )

    add_custom_target(coverage-html
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/coverage_html
        COMMAND gcovr -r ${PROJECT_SOURCE_DIR}/src
            --object-directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/sweetc.dir/src/
            --html-details coverage_html/coverage
        )

    add_subdirectory(src/testing testing)
endif()

if (BUILD_TESTS OR "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    enable_testing()
    add_subdirectory(tests)
endif()
