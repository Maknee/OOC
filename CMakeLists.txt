cmake_minimum_required (VERSION 3.5)

project (OOC)

option(BUILD_OOC_TESTS "Build tests" OFF) #Only build for gcc currently... Should transfer to google test or ctest

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") #Only build for gcc
    set(CMAKE_C_FLAGS "-Werror -Wextra -Wall -std=c11 -fms-extensions")
endif()

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)

