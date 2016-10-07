project(kaddressbookimportexport)
ecm_setup_version(${KDEPIM_APPS_LIB_VERSION} VARIABLE_PREFIX KADDRESSBOOKIMPORTEXPORT
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/kaddressbookimportexport_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookImportExportConfigVersion.cmake"
                        SOVERSION 5
)

########### Targets ###########

add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5KaddressbookImportExport")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5KaddressbookImportExportConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookImportExportConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookImportExportConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5KaddressbookImportExportConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5KaddressbookImportExportTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5KaddressbookImportExportTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/kaddressbookimportexport_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

add_subdirectory(src)
