project(OpenDeathValley)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_BINARY_DIR}/bin)

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
else()
  set(CMAKE_C_FLAGS "-Wall -W -Werror -pedantic -std=c99")
endif()

add_subdirectory(components/files)
add_subdirectory(test)
