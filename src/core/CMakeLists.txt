set(INCROOT ${CMAKE_SOURCE_DIR}/src/core)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/core)

set(HEADER_FILES
	${INCROOT}/odv_file.h
)

set(SRC_FILES
	${SRCROOT}/odv_file.c
)

add_library(core ${HEADER_FILES} ${SRC_FILES})