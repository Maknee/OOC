project(Vector-Shopping_Adding_Template_Example)

add_executable(${PROJECT_NAME} vector_example.c)

target_link_libraries(${PROJECT_NAME}
    OOC::Library
    )

