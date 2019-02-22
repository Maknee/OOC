project(OOC_Library)

add_library(${PROJECT_NAME} 
    ooc_container.c
    ooc_error.c
    ooc_object.c
    ooc_entry.c
    ooc_map.c
    ooc_map_template.c
    ooc_program.c
    ooc_set.c
    ooc_set_template.c
    ooc_string.c
    ooc_vector.c
    ooc_vector_template.c
    ooc_rtti.c
    ooc_template.c

    ooc_container.h
    ooc_error.h
    ooc_object.h
    ooc.h
    ooc_entry.h
    ooc_map.h
    ooc_map_template.h
    ooc_set.h
    ooc_set_template.h
    ooc_string.h
    ooc_vector.h
    ooc_vector_template.h
    ooc_rtti.h
    ooc_template.h
    )

add_library(OOC::Library ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/
    )
