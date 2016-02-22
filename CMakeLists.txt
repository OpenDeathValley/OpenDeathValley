project(OpenDeathValley)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMakeTests)

macro(replace_flags var these those)
    if ("${${var}}" MATCHES "${these}")
        string(REGEX REPLACE "${these}" "${those}" ${var} "${${var}}")
        message(STATUS "info: ${var} changed to '${${var}}'")
    endif()
    message(STATUS "info: ${var}='${${var}}'")
endmacro()

macro(msvc_link_to_static_crt)
    if (MSVC)
        set(has_correct_flag 0)
        foreach(lang C CXX)
            foreach(suffix "" _DEBUG _MINSIZEREL _RELEASE _RELWITHDEBINFO)
                replace_flags("CMAKE_${lang}_FLAGS${suffix}" "/MD" "/MT")
            endforeach()
        endforeach()
    endif()
endmacro()

if(MSVC)
  add_definitions(-DWINDOWS)
  # With C89 we're forced to use non-secure functions
  add_definitions(/D _CRT_SECURE_NO_WARNINGS)
  #    force treat warnings as errors: /WX
  #    force warning level 4
  #
  foreach(lang C CXX)
    if("${CMAKE_${lang}_FLAGS}" MATCHES "/W[1-3]")
      string(REGEX REPLACE "/W[1-3]" "/W4 /WX" CMAKE_${lang}_FLAGS "${CMAKE_${lang}_FLAGS}")
      message(STATUS "Replacing /W[1-3] with /W4 /WX...")
    else("${CMAKE_${lang}_FLAGS}" MATCHES "/W[1-3]")
      set(CMAKE_${lang}_FLAGS "${CMAKE_${lang}_FLAGS} /W4 /WX")
      message(STATUS "Adding /W4 /WX...")
    endif("${CMAKE_${lang}_FLAGS}" MATCHES "/W[1-3]")
  endforeach(lang)
  msvc_link_to_static_crt()
else()
  set(CMAKE_C_FLAGS "-Wall -W -Werror -pedantic -std=c99")
endif()

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    SET(LINK_LIBS ${LINK_LIBS} ${ZLIB_LIBRARIES})
endif(ZLIB_FOUND)

find_package (BZip2 REQUIRED)
if (BZIP2_FOUND)
  include_directories(${BZIP_INCLUDE_DIRS})
  SET(LINK_LIBS ${LINK_LIBS} ${BZIP2_LIBRARIES})
endif (BZIP2_FOUND)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(components/files)
add_subdirectory(apps/files_test)
