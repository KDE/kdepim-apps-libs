cmake_minimum_required(VERSION 3.5)
set(PIM_VERSION "5.15.80")
project(kdepim-apps-lib VERSION ${PIM_VERSION})

set(KF5_MIN_VERSION "5.75.0")

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

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
