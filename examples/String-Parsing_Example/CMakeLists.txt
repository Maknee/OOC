project(String_Parsing_Example)

add_executable(${PROJECT_NAME} string_example.c)

target_link_libraries(${PROJECT_NAME}
    OOC::Library
    )

