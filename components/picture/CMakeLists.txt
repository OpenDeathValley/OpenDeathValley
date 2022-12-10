include_directories(${CMAKE_SOURCE_DIR}/components/files/)
include_directories(${CMAKE_SOURCE_DIR}/components/util/)

set(ODV_PICTURE_SRC
    odv_image.c
    odv_imagemap.c
)

add_library(odv_component_picture ${ODV_PICTURE_SRC})

