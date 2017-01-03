ecm_setup_version(PROJECT VARIABLE_PREFIX KADDRESSBOOKGRANTLEE
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kaddressbookgrantlee_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookGrantleeConfigVersion.cmake"
                        SOVERSION 5
)

########### Targets ###########

add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5KaddressbookGrantlee")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5KaddressbookGrantleeConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookGrantleeConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookGrantleeConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookGrantleeConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5KaddressbookGrantleeTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5KaddressbookGrantleeTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/kaddressbookgrantlee_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

add_subdirectory(src)

