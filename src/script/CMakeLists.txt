include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/core
)

set(INCROOT ${CMAKE_SOURCE_DIR}/src/script)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/script)

set(HEADER_FILES
    ${INCROOT}/odv_scb_handler.h
    ${INCROOT}/odv_scb_disassembler.h
)

set(SRC_FILES
    ${SRCROOT}/odv_scb_handler.c
    ${SRCROOT}/odv_scb_disassembler.c
)

add_library(script ${HEADER_FILES} ${SRC_FILES})

add_dependencies(script
core)

target_link_libraries(script
core)