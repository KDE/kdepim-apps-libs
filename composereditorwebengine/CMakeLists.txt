project(composereditorwebengine)

ecm_setup_version(${KDEPIM_APPS_LIB_VERSION} VARIABLE_PREFIX COMPOSEREDITORWEBENGINE
                        VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/composereditorwebengine_version.h"
                        PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5ComposerEditorWebEngineConfigVersion.cmake"
                        SOVERSION 5
)

########### Targets ###########

add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5ComposerEditorWebEngine")

ecm_configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/KF5ComposerEditorWebEngineConfig.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5ComposerEditorWebEngineConfig.cmake"
  INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/KF5ComposerEditorWebEngineConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/KF5ComposerEditorWebEngineConfigVersion.cmake"
  DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
  COMPONENT Devel
)

install(EXPORT KF5ComposerEditorWebEngineTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5ComposerEditorWebEngineTargets.cmake NAMESPACE KF5::)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/composereditorwebengine_version.h
  DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5} COMPONENT Devel
)

add_subdirectory(src)
if (BUILD_TESTING)
   #add_subdirectory(autotests)
   #add_subdirectory(tests)
endif()
