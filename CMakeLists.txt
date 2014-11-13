project(odv_tools)

cmake_minimum_required(VERSION 2.8)

#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)

IF(MSVC)
  add_definitions(-DWINDOWS)
  # With C89 we're forced to use non-secure functions
  add_definitions(/D _CRT_SECURE_NO_WARNINGS)
  #    force treat warnings as errors: /WX
  #    force warning level 4
  #
  FOREACH(lang C CXX)
    IF("${CMAKE_${lang}_FLAGS}" MATCHES "/W[1-3]")
      STRING(REGEX REPLACE "/W[1-3]" "/W4 /WX" CMAKE_${lang}_FLAGS "${CMAKE_${lang}_FLAGS}")
      MESSAGE(STATUS "Replacing /W[1-3] with /W4 /WX...")
    ELSE("${CMAKE_${lang}_FLAGS}" MATCHES "/W[1-3]")
      SET(CMAKE_${lang}_FLAGS "${CMAKE_${lang}_FLAGS} /W4 /WX")
      MESSAGE(STATUS "Adding /W4 /WX...")
    ENDIF("${CMAKE_${lang}_FLAGS}" MATCHES "/W[1-3]")
  ENDFOREACH(lang)
ENDIF(MSVC)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(-Wall -W -Werror -pedantic)
endif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

add_subdirectory(src)