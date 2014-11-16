include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src/core)

set(INCROOT ${CMAKE_SOURCE_DIR}/src/sounds)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/sounds)

set(HEADER_FILES
    ${INCROOT}/odv_fxg_handler.h
)

set(SRC_FILES
    ${SRCROOT}/odv_fxg_handler.c
)

add_library(sounds ${HEADER_FILES} ${SRC_FILES})

add_dependencies(sounds
core)

target_link_libraries(sounds
core)