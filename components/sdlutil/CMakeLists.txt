include_directories(${CMAKE_SOURCE_DIR}/components/files)
include_directories(${CMAKE_SOURCE_DIR}/components/resource)
include_directories(${CMAKE_SOURCE_DIR}/components/picture/)
include_directories(${CMAKE_SOURCE_DIR}/components/util/)


set(ODV_SDLUTIL_SRC
    odv_image_to_surface.c)
    
add_library(odv_component_sdlutil ${ODV_SDLUTIL_SRC})

