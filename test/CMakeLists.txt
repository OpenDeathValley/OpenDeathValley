include_directories(${CMAKE_SOURCE_DIR}/components/files)

set(TEST_SRC
	odv_test.c)

add_executable(odv_test
    ${TEST_SRC})

target_link_libraries(odv_test
    odv_component_files)

