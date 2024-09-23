message("set iterative_methods")

add_library(iterative_methods STATIC)
target_sources(iterative_methods
    PRIVATE
        iterative_methods-impl.cpp
    PUBLIC
        FILE_SET CXX_MODULES
        FILES
            iterative_methods-interface.cppm
)
target_compile_features(iterative_methods PUBLIC cxx_std_20)

include(GenerateExportHeader)
generate_export_header(iterative_methods)
target_sources(iterative_methods
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/iterative_methods_export.h
)

target_link_libraries(iterative_methods PUBLIC Eigen3::Eigen)


