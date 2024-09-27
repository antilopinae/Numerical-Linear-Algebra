cmake_minimum_required(VERSION 3.26.0)

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

FetchContent_Declare(matplotlib_cpp
  GIT_REPOSITORY git@github.com:lava/matplotlib-cpp.git
  GIT_TAG ef0383f1315d32e0156335e10b82e90b334f6d9f # Important: Specify a version or a commit hash here.
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/extern/matplotlib_cpp-src
  BINARY_DIR ${CMAKE_BINARY_DIR}/extern/matplotlib_cpp
)

option(MATPLOTLIB_CPP_ENABLE_INSTALL "" OFF)
option(MATPLOTLIB_CPP_BUILD_EXAMPLES "" OFF)
option(MATPLOTLIB_CPP_BUILD_DOCS "" OFF)

FetchContent_MakeAvailable(matplotlib_cpp)

