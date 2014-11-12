project(odv_tools)

cmake_minimum_required(VERSION 2.8)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if(WIN32)
  if(NOT WINDOWS)
    set(WINDOWS TRUE)
  endif()
endif()

add_subdirectory(src)