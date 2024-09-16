cmake_minimum_required(VERSION 3.26.0)

set(GMTL_CMAKE_GMTL_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/extern)
set(GMTL_CMAKE_GMTL_TAG "5ac14d8411d47795c1d7d67b6bc26fa7a747b9c4")

if(NOT DEFINED GMTL_CMAKE_GMTL_TAG)
  message(FATAL_ERROR "You must specify GMTL_CMAKE_GMTL_TAG!")
endif()

if(NOT DEFINED GMTL_CMAKE_GMTL_SOURCE_DIR)
  set(GMTL_CMAKE_GMTL_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

set(GMTL_CMAKE_GMTL_DEP_DIR "${GMTL_CMAKE_GMTL_SOURCE_DIR}/gmtl-${GMTL_CMAKE_GMTL_TAG}-src")

include(FetchContent)

FetchContent_Declare(gmtl
  GIT_REPOSITORY  git@github.com:imvu/gmtl.git
  GIT_TAG         ${GMTL_CMAKE_GMTL_TAG}
  GIT_SHALLOW     TRUE
  SOURCE_DIR      ${GMTL_CMAKE_GMTL_DEP_DIR}
)

option(gmtl_ENABLE_INSTALL "" OFF)
option(gmtl_BUILD_EXAMPLES "" OFF)
option(gmtl_BUILD_DOCS "" OFF)

FetchContent_GetProperties(gmtl)

if(NOT gmtl_POPULATED)
  message(STATUS "Fetching gmtl ${GMTL_CMAKE_GMTL_TAG}")

  if(EXISTS "${GMTL_CMAKE_GMTL_DEP_DIR}/gmtl")
    set(FETCHCONTENT_SOURCE_DIR_GMTL ${GMTL_CMAKE_GMTL_DEP_DIR})
    message(STATUS "gmtl ${GMTL_CMAKE_GMTL_TAG} source found at ${GMTL_CMAKE_GMTL_DEP_DIR}; skip fetching.")
  endif()

  FetchContent_MakeAvailable(gmtl)
  message(STATUS "Populating gmtl ${GMTL_CMAKE_GMTL_TAG} done; src at ${gmtl_SOURCE_DIR}")
endif()

add_library(gmtl INTERFACE)

target_include_directories(gmtl
  INTERFACE
        ${gmtl_SOURCE_DIR}
)

target_compile_definitions(gmtl
  INTERFACE
    GMTL_STANDALONE
    GMTL_NO_DEPRECATED
)

if(UNIX)
  target_link_libraries(gmtl
    INTERFACE pthread
  )
elseif(WIN32)
  # macro see @ https://stackoverflow.com/a/40217291/1746503
  macro(get_WIN32_WINNT version)
    if (CMAKE_SYSTEM_VERSION)
      set(ver ${CMAKE_SYSTEM_VERSION})
      string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
      string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
      # Check for Windows 10, b/c we'll need to convert to hex 'A'.
      if ("${verMajor}" MATCHES "10")
        set(verMajor "A")
        string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
      endif ("${verMajor}" MATCHES "10")
      # Remove all remaining '.' characters.
      string(REPLACE "." "" ver ${ver})
      # Prepend each digit with a zero.
      string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
      set(${version} "0x${ver}")
    endif(CMAKE_SYSTEM_VERSION)
  endmacro(get_WIN32_WINNT)

  if(NOT DEFINED _WIN32_WINNT)
    get_WIN32_WINNT(ver)
    set(_WIN32_WINNT ${ver})
  endif()

  message(STATUS "Set _WIN32_WINNET=${_WIN32_WINNT}")

  target_compile_definitions(gmtl
    INTERFACE
      _WIN32_WINNT=${_WIN32_WINNT}
      WIN32_LEAN_AND_MEAN
  )
endif()
