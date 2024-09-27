include(GetFTXUI)
include(GetEigen3)
include(GetGMTL)

add_library(num_console_static STATIC tui.cpp)
target_include_directories(num_console_static PUBLIC include)
target_precompile_headers(num_console_static PUBLIC <string>)

target_link_libraries(num_console_static PUBLIC
    calc_static
    ftxui::screen ftxui::dom ftxui::component
    Eigen3::Eigen
    gmtl
)

include(Optimized)
Optimized(num_console_static)

include(BuildInfo)
BuildInfo(num_console_static)

include(Coverage)
CleanCoverage(num_console_static)

include(Format)
Format(num_console_static .)

include(CppCheck)
# AddCppCheck(num_console_static)

include(Doxygen)
Doxygen(num_console src/num_console)

add_executable(num_console bootstrap.cpp)
target_link_libraries(num_console num_console_static)
