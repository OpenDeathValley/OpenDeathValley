include_directories(${CMAKE_SOURCE_DIR}/components/files)

set(FILES_TEST_SRC
    odv_files_test.c)

add_executable(odv_files_test ${FILES_TEST_SRC})

target_link_libraries(odv_files_test odv_component_files ${LINK_LIBS})

