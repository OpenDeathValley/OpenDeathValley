include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/core)
include_directories(${CMAKE_SOURCE_DIR}/src/resources)
include_directories(${CMAKE_SOURCE_DIR}/src/script)
include_directories(${CMAKE_SOURCE_DIR}/src/sounds)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)

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
sounds
core)

target_link_libraries(odv_test
resources
script
sounds
core)