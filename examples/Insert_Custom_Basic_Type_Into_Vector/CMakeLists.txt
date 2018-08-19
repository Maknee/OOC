project(Insert_Custom_Basic_Type_Into_Vector)

add_executable(${PROJECT_NAME} custom_basic_type_vector_example.c example_struct.c)

target_link_libraries(${PROJECT_NAME}
    OOC::Library
    )

