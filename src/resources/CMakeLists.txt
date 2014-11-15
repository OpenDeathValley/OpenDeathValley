include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/core)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

set(INCROOT ${CMAKE_SOURCE_DIR}/src/resources)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/resources)

set(HEADER_FILES
	${INCROOT}/odv_resource_handler.h
    ${INCROOT}/odv_resource_wave.h
    ${INCROOT}/odv_resource_text.h
)

set(SRC_FILES
	${SRCROOT}/odv_resource_handler.c
    ${SRCROOT}/odv_resource_wave.c
    ${SRCROOT}/odv_resource_text.c
)

add_library(resources ${HEADER_FILES} ${SRC_FILES})

add_dependencies(resources core utils)

target_link_libraries(resources core utils)