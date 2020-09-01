cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.15.40")
project(kdepim-apps-lib VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.73.0")

find_package(ECM ${KF5_MIN_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
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

set(QT_REQUIRED_VERSION "5.13.0")

set(AKONADI_VERSION "5.15.40")
set(GRANTLEETHEME_LIB_VERSION "5.15.40")
set(AKONADICONTACT_LIB_VERSION "5.15.40")
set(LIBKLEO_LIB_VERSION "5.15.40")
set(PIMCOMMON_LIB_VERSION "5.15.40")
set(GRANTLEE_LIB_VERSION "5.2")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Gui)

find_package(KF5Config ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5ConfigWidgets ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5Contacts ${KF5_MIN_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_MIN_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5ContactEditor ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)

find_package(Grantlee5 ${GRANTLEE_LIB_VERSION} CONFIG REQUIRED)

if(BUILD_TESTING)
    find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Test)
    add_definitions(-DBUILD_TESTING)
endif()
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x050e00)
add_definitions(-DKF_DISABLE_DEPRECATED_BEFORE_AND_AT=0x054A00)

add_definitions(-DQT_NO_FOREACH)
add_definitions(-DQT_NO_KEYWORDS)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(kaddressbookgrantlee)
add_subdirectory(kaddressbookimportexport)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

ecm_qt_install_logging_categories(
        EXPORT KDEPIMAPPSLIB
        FILE kdepim-apps-lib.categories
        DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR}
        )
