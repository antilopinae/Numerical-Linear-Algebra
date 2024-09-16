include(GNUInstallDirs)

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
