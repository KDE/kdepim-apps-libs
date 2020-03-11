cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.13.80")
project(kdepim-apps-lib VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.68.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)
if (POLICY CMP0053)
    cmake_policy(SET CMP0053 NEW)
endif()

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)

include(ECMSetupVersion)
include(FeatureSummary)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)



set(KDEPIM_APPS_LIB_VERSION ${PIM_VERSION})

set(QT_REQUIRED_VERSION "5.12.0")

set(AKONADI_VERSION "5.13.40")
set(GRANTLEETHEME_LIB_VERSION "5.13.40")
set(AKONADICONTACT_LIB_VERSION "5.13.40")
set(LIBKLEO_LIB_VERSION "5.13.40")
set(PIMCOMMON_LIB_VERSION "5.13.40")
set(GRANTLEE_LIB_VERSION "5.2")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets DBus Gui)

find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ConfigWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5WidgetsAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Contacts ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ContactEditor ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)

find_package(Grantlee5 ${GRANTLEE_LIB_VERSION} CONFIG REQUIRED)

find_package(KF5Prison ${KF5_MIN_VERSION} CONFIG REQUIRED)

if(BUILD_TESTING)
    find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Test)
    add_definitions(-DBUILD_TESTING)
endif()
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
   add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
   add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x060000)
endif()

add_definitions(-DQT_NO_FOREACH)

add_subdirectory(libfollowupreminder)
add_subdirectory(libkdepimdbusinterfaces)
add_subdirectory(libsendlater)
add_subdirectory(kaddressbookgrantlee)
add_subdirectory(kaddressbookimportexport)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

if (ECM_VERSION VERSION_LESS "5.68.0")
    install(FILES kdepim-apps-lib.renamecategories kdepim-apps-lib.categories  DESTINATION  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
else ()
    ecm_qt_install_logging_categories(
        EXPORT KDEPIMAPPSLIB
        FILE kdepim-apps-lib.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )
endif()
