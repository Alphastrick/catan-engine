cmake_minimum_required(VERSION 3.15)

set(VERSION 1.0.0)

project(
    catan_engine
    VERSION ${VERSION}
)

file(GLOB_RECURSE src       src/*.cpp)
file(GLOB_RECURSE tests     tests/*.cpp)

set (CMAKE_CXX_STANDARD 20)

if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>")
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    endif()
endif()

# Application

add_library(
    catan_engine_lib
    ${src}
)

target_include_directories(
    catan_engine_lib
    PUBLIC
    include/
)

# Testing

add_subdirectory(
    lib/google_test
)

# add_subdirectory(
#     lib/google_fuzztest
# )

enable_testing()
add_executable(
    catan_engine_unit_tests ${tests}
)

target_link_libraries(
    catan_engine_unit_tests PUBLIC
    gtest_main catan_engine_lib
)

target_include_directories(
    catan_engine_unit_tests PUBLIC
    ${gtest_SOURCE_DIR}/include
    ${gmock_SOURCE_DIR}/include
)

target_include_directories(
    catan_engine_unit_tests
    PUBLIC
    include/
)

add_test(
    unit_tests catan_engine_unit_tests
)
