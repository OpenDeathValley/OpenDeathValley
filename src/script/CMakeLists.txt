set(INCROOT ${CMAKE_SOURCE_DIR}/src/script)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/script)

set(SRC ${SRCROOT}/ODVSCBManager.c)

add_library(script ${SRC})