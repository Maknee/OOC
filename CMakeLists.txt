cmake_minimum_required (VERSION 3.5)

project (OOC)

option(BUILD_OOC_TESTS "Build tests" OFF) #Only build for gcc currently... Should transfer to google test or ctest

if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang" ) #Only build for gcc/clang
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wextra -Wall -Wno-unused-parameter -std=c11 -fms-extensions")
    set(CAN_BUILD_TESTS TRUE)
endif()

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)

