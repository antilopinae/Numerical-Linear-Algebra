cmake_minimum_required(VERSION 3.26.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
project(Maxima VERSION 1.0.0 LANGUAGES CXX)
enable_testing()

set(LLVM_ENABLE_PROJECTS "clang" CACHE INTERNAL "" FORCE)
set(CMAKE_C_COMPILER "/usr/bin/clang" CACHE INTERNAL "" FORCE)
set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE INTERNAL "" FORCE)
set (CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" FORCE)

set(CMAKE_BUILD_TYPE "Debug" CACHE INTERNAL "" FORCE)
# I want to DEBUG !!!

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE CACHE INTERNAL "" FORCE)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
# Default to C++ extensions being off. Clang's modules support have trouble
# with extensions right now.

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(CMAKE_CXX_SCAN_FOR_MODULES YES)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "clang")
  set(CMAKE_EXE_LINKER_FLAGS -lstdc++)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  include(GCC_Modules.cmake)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(NoInSourceBuilds)

add_subdirectory(src bin)
add_subdirectory(modules)
add_subdirectory(test)

include(Install)
