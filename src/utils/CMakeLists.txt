set(INCROOT ${CMAKE_SOURCE_DIR}/src/utils)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/utils)

set(HEADER_FILES
	${INCROOT}/odv_utils.h
)

set(SRC_FILES
	${SRCROOT}/odv_utils.c
)

add_library(utils ${HEADER_FILES} ${SRC_FILES})