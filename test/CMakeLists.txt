project(OOC_Tests)

if (BUILD_OOC_TEST)
    if ("${CMAKE_GXX_COMPILER_ID}" STREQUAL "GNU") #Only build for gcc
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
