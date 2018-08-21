project(Constructing_A_Default_Class)

add_executable(${PROJECT_NAME} constructing_a_default_class.c default_example_struct.c)

target_link_libraries(${PROJECT_NAME}
    OOC::Library
    )

