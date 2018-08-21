project(String-Parsing_Example)

add_executable(${PROJECT_NAME} string_example.c)
add_executable(${PROJECT_NAME}_cpp string_example.cpp)

target_link_libraries(${PROJECT_NAME}
    OOC::Library
    )

