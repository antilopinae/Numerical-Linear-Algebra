add_executable(num_console_test tui_test.cpp)
target_link_libraries(num_console_test
                      PRIVATE num_console_static)
AddTests(num_console_test)
EnableCoverage(num_console_static)
