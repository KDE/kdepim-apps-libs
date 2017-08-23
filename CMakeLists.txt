cmake_minimum_required(VERSION 3.0)
set(PIM_VERSION "5.6.1")
project(kdepim-apps-lib VERSION ${PIM_VERSION})

set(KF5_VERSION "5.35.0")
find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(CMakePackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)
include(ECMCoverageOption)


set(KDEPIM_APPS_LIB_VERSION ${PIM_VERSION})

set(QT_REQUIRED_VERSION "5.7.0")

set(AKONADI_VERSION "5.6.0")
set(GRANTLEETHEME_LIB_VERSION "5.6.0")
set(KCONTACTS_LIB_VERSION "5.6.0")
set(AKONADICONTACT_LIB_VERSION "5.6.0")
set(LIBKLEO_LIB_VERSION "5.6.0")
set(PIMCOMMON_LIB_VERSION "5.6.0")

find_package(Qt5 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Widgets Test DBus Gui)

find_package(KF5Config ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5ConfigWidgets ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5CoreAddons ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5I18n ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5IconThemes ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5KIO ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5Service ${KF5_VERSION} CONFIG REQUIRED)
find_package(KF5WidgetsAddons ${KF5_VERSION} CONFIG REQUIRED)

find_package(KF5Akonadi ${AKONADI_VERSION} CONFIG REQUIRED)
find_package(KF5AkonadiContact ${AKONADICONTACT_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Contacts ${KCONTACTS_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5GrantleeTheme ${GRANTLEETHEME_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5Libkleo ${LIBKLEO_LIB_VERSION} CONFIG REQUIRED)
find_package(KF5PimCommonAkonadi ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)

find_package(Grantlee5 "5.1" CONFIG REQUIRED)

find_package(KF5Prison ${KF5_VERSION})
set_package_properties(Prison PROPERTIES
    DESCRIPTION "Prison"
    URL "http://projects.kde.org/prison"
    TYPE OPTIONAL
    PURPOSE "Needed to show mobile barcodes of your contacts")

if(BUILD_TESTING)
   add_definitions(-DBUILD_TESTING)
endif(BUILD_TESTING)
add_definitions(-DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
add_definitions("-DQT_NO_CAST_FROM_ASCII -DQT_NO_CAST_TO_ASCII")
add_definitions(-DQT_NO_NARROWING_CONVERSIONS_IN_CONNECT)
add_definitions(-DQT_NO_URL_CAST_FROM_STRING)
add_subdirectory(libfollowupreminder)
add_subdirectory(libkdepimdbusinterfaces)
add_subdirectory(libsendlater)
add_subdirectory(kaddressbookgrantlee)
add_subdirectory(kaddressbookimportexport)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

install( FILES kdepim-apps-lib.renamecategories kdepim-apps-lib.categories DESTINATION ${KDE_INSTALL_CONFDIR} )
