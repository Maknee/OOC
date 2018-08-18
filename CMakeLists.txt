cmake_minimum_required (VERSION 3.5)

project (OOC)

option(BUILD_OOC_TESTS "Build tests" OFF) #Only build for gcc currently... Should transfer to google test or ctest

add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(test)

