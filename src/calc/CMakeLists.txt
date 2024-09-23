add_library(calc_static STATIC calc.cpp)
target_include_directories(calc_static INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

target_link_libraries(calc_static PRIVATE iterative_methods)

set_target_properties(calc_static PROPERTIES
    PUBLIC_HEADER src/calc/include/calc/calc.h
    POSITION_INDEPENDENT_CODE 1
)

include(Optimized)
Optimized(calc_static)

include(Coverage)
CleanCoverage(calc_static)

include(Format)
Format(calc_static .)

include(CppCheck)
AddCppCheck(calc_static)

include(Doxygen)
Doxygen(calc src/calc)
