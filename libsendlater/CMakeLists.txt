ecm_setup_version(PROJECT  VARIABLE_PREFIX SENDLATER
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/sendlater_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5SendLaterConfigVersion.cmake"
                        SOVERSION 5
)


########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5SendLater")

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5SendLaterConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SendLaterConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SendLaterConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5SendLaterConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5SendLaterTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5SendLaterTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/sendlater_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

add_subdirectory(src)

