include_directories(${CMAKE_SOURCE_DIR}/components/files/)

set(ODV_UTIL_SRC
    odv_utils.c
)

add_library(odv_component_util ${ODV_UTIL_SRC})

