include_directories(${CMAKE_SOURCE_DIR}/components/files)
include_directories(${CMAKE_SOURCE_DIR}/components/files/resource)
include_directories(${CMAKE_SOURCE_DIR}/components/picture/)
include_directories(${CMAKE_SOURCE_DIR}/components/util/)
include_directories(${CMAKE_SOURCE_DIR}/components/sdlutil)

set(FILES_TEST_SRC odv_files_test.c)

set(FILES_SDL_TEST_SRC odv_sdl_test.c)

add_executable(odv_files_test ${FILES_TEST_SRC})
add_executable(odv_sdl_test ${FILES_SDL_TEST_SRC})

target_link_libraries(odv_files_test ${odv_components} ${LINK_LIBS})

if(WIN32)
target_link_libraries(odv_sdl_test ${odv_components} odv_component_sdlutil ${LINK_LIBS} ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})
else()
target_link_libraries(odv_sdl_test ${odv_components} odv_component_sdlutil ${LINK_LIBS} ${SDL2_LIBRARY})
endif()