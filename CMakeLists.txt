project(kdepim-apps-lib)
cmake_minimum_required(VERSION 2.8.12)

set(KF5_VERSION "5.26.0")
find_package(ECM ${KF5_VERSION} CONFIG REQUIRED)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
set(LIBRARY_NAMELINK)
include(GenerateExportHeader)
include(ECMGenerateHeaders)
include(ECMGeneratePriFile)
include(ECMPackageConfigHelpers)
include(ECMSetupVersion)
include(FeatureSummary)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(ECMQtDeclareLoggingCategory)
include(ECMAddTests)

set(PIM_VERSION "5.3.47")
set(KDEPIM_APPS_LIB_VERSION ${PIM_VERSION})

set(QT_REQUIRED_VERSION "5.6.0")

set(AKONADI_VERSION "5.3.40")
set(GRANTLEETHEME_LIB_VERSION "5.3.40")
set(KCONTACTS_LIB_VERSION "5.3.40")
set(AKONADICONTACT_LIB_VERSION "5.3.40")
set(LIBKLEO_LIB_VERSION "5.3.40")
set(PIMCOMMON_LIB_VERSION "5.3.40")

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
find_package(KF5PimCommon ${PIMCOMMON_LIB_VERSION} CONFIG REQUIRED)

find_package(Grantlee5 "5.1" CONFIG REQUIRED)

find_package(KF5Prison ${KF5_VERSION})
set_package_properties(Prison PROPERTIES
    DESCRIPTION "Prison"
    URL "http://projects.kde.org/prison"
    TYPE OPTIONAL
    PURPOSE "Needed to show mobile barcodes of your contacts")


add_subdirectory(libfollowupreminder)
add_subdirectory(libkdepimdbusinterfaces)
add_subdirectory(libsendlater)
add_subdirectory(kaddressbookgrantlee)
add_subdirectory(kaddressbookimportexport)
feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

install( FILES kdepim-apps-lib.renamecategories kdepim-apps-lib.categories DESTINATION ${KDE_INSTALL_CONFDIR} )
