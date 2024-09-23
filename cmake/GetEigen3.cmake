set(Eigen_CMAKE_Eigen_TAG "3.4.0") #3.4.0 - last version
set(Eigen_CMAKE_Eigen_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/extern)

if(NOT DEFINED Eigen_CMAKE_Eigen_TAG)
  message(FATAL_ERROR "You must specify Eigen_CMAKE_Eigen_TAG!")
endif()

if(NOT DEFINED Eigen_CMAKE_Eigen_SOURCE_DIR)
  set(Eigen_CMAKE_Eigen_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})
endif()

set(Eigen_CMAKE_Eigen_DEP_DIR "${Eigen_CMAKE_Eigen_SOURCE_DIR}/eigen-${Eigen_CMAKE_Eigen_TAG}-src")

include(FetchContent)

FetchContent_Declare(Eigen3
  GIT_REPOSITORY  https://gitlab.com/libeigen/eigen
  GIT_TAG         ${Eigen_CMAKE_Eigen_TAG}
  GIT_SHALLOW     TRUE
  SOURCE_DIR      ${Eigen_CMAKE_Eigen_DEP_DIR}
)

option(Eigen3_ENABLE_INSTALL "" OFF)
option(Eigen3_BUILD_EXAMPLES "" OFF)
option(Eigen3_BUILD_DOCS "" OFF)

FetchContent_MakeAvailable(Eigen3)
