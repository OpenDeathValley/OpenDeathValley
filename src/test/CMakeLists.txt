include_directories(
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/src/core
	${CMAKE_SOURCE_DIR}/src/resources
    ${CMAKE_SOURCE_DIR}/src/script
)

set(INCROOT ${CMAKE_SOURCE_DIR}/src/test)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/test)

set(HEADER_FILES
	${INCROOT}/odv_test.h
)

set(SRC_FILES
	${SRCROOT}/odv_test.c
)

add_executable(odv_test
${HEADER_FILES}
${SRC_FILES}
)

add_dependencies(odv_test
resources
script
core)

target_link_libraries(odv_test
resources
script
core)