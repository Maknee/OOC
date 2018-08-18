project(OOC_Tests)

if (BUILD_OOC_TEST)
    if (${CAN_BUILD_TESTS}) 
        set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage -O0 -g -ftrapv -Werror -Wextra -Wall -Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wwrite-strings -Waggregate-return -Wswitch-default -Wswitch-enum -Wconversion -Wunreachable-code -Winit-self -Wformat-nonliteral -Wno-unused-parameter -Wno-unused-but-set-parameter -std=c11 -fms-extensions -ggdb3")
        set(CMAKE_EXE_LINKER_FLAGS "-lcunit")
        add_executable(${PROJECT_NAME} 
            cunit_test_driver.c
            ooc_casts_cuint_test.c
            ooc_container_cunit_test.c
            ooc_map_cuint_test.c
            ooc_object_cunit_test.c
            ooc_set_cuint_test.c
            ooc_string_cunit_test.c
            ooc_vector_cuint_test.c

            ooc_casts_cuint_test.h
            ooc_container_cunit_test.h
            ooc_map_cuint_test.h
            ooc_object_cunit_test.h
            ooc_set_cuint_test.h
            ooc_string_cunit_test.h
            ooc_vector_cuint_test.h
            )

        target_link_libraries(${PROJECT_NAME}
            OOC::Library
            )
    endif()
endif(BUILD_OOC_TEST)
