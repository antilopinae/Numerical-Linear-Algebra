include(GNUInstallDirs)

install(TARGETS iterative_methods
    EXPORT my_package-targets
    # ... a few details omitted, see the "Deep CMake For Library Authors" talk
    FILE_SET CXX_MODULES
        # There's currently no convention for this location, see discussion below
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_package/src
    FILE_SET HEADERS
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}   # Same as default, could be omitted
    INCLUDES
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT my_package-targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_package
    CXX_MODULES_DIRECTORY .
)
# The following file includes the my_package-targets.cmake file
install(FILES my_package-config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/my_package
)

# Calc library
install(TARGETS calc_static
  EXPORT CalcLibrary
  ARCHIVE COMPONENT development
  LIBRARY COMPONENT runtime
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/calc
    COMPONENT runtime
)

if (UNIX)
  install(CODE "execute_process(COMMAND ldconfig)"
          COMPONENT runtime
  )
endif()

install(EXPORT CalcLibrary
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake
  NAMESPACE Calc::
  COMPONENT runtime
)

install(FILES "CalcConfig.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/calc/cmake
)

# CalcConsole runtime
install(TARGETS calc_console
  RUNTIME COMPONENT runtime
)

# CPack configuration
set(CPACK_PACKAGE_VENDOR "ANTILOPA")
set(CPACK_PACKAGE_CONTACT "mikbas31@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION "Simple Calculator")
include(CPack)
