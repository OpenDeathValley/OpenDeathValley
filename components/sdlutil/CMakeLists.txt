include_directories(${CMAKE_SOURCE_DIR}/components/files)

set(ODV_SDLUTIL_SRC
    odv_image_to_surface.c)
    
add_library(odv_components_sdlutil ${ODV_SDLUTIL_SRC})

