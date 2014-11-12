include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/core
)

set(INCROOT ${CMAKE_SOURCE_DIR}/src/resources)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/resources)

set(HEADER_FILES
	${INCROOT}/odv_resource_handler.h
)

set(SRC_FILES
	${SRCROOT}/odv_resource_handler.c
)

add_library(resources ${HEADER_FILES} ${SRC_FILES})

add_dependencies(resources
core)

target_link_libraries(resources
core)