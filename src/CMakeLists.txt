project(OOC_Library)

add_library(${PROJECT_NAME} 
    container.c
    error.c
    object.c
    ooc_entry.c
    ooc_map.c
    ooc_map_template.c
    ooc_program.c
    ooc_set.c
    ooc_set_template.c
    ooc_string.c
    ooc_vector.c
    ooc_vector_template.c
    rtti.c
    template.c

    container.h
    error.h
    object.h
    ooc.h
    ooc_entry.h
    ooc_map.h
    ooc_map_template.h
    ooc_set.h
    ooc_set_template.h
    ooc_string.h
    ooc_vector.h
    ooc_vector_template.h
    rtti.h
    template.h
    )

add_library(OOC::Library ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/
    )
