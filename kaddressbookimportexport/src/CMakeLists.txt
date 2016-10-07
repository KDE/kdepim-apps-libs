add_definitions( -DQT_NO_CAST_FROM_ASCII )
add_definitions( -DQT_NO_CAST_TO_ASCII )
add_definitions(-DTRANSLATION_DOMAIN=\"libkaddressbookimportexport\")

set(kaddressbook_importexport_LIB_SRCS
   kaddressbookimportexportplugin.cpp
)

add_library(KF5KaddressbookImportExport ${kaddressbook_importexport_LIB_SRCS})
generate_export_header(KF5KaddressbookImportExport BASE_NAME kaddressbook_importexport)

add_library(KF5::KaddressbookImportExport ALIAS KF5KaddressbookImportExport)

target_include_directories(KF5KaddressbookImportExport INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KaddressbookImportExport/;${KDE_INSTALL_INCLUDEDIR_KF5}/kaddressbookimportexport>")
target_include_directories(KF5KaddressbookImportExport PUBLIC "$<BUILD_INTERFACE:${kaddressbookimportexport_SOURCE_DIR}/src;${kaddressbookimportexport_BINARY_DIR}/src;${Grantlee_INCLUDE_DIRS}>")


target_link_libraries(KF5KaddressbookImportExport
PRIVATE
  KF5::ConfigWidgets
  KF5::Service
  KF5::IconThemes
  KF5::I18n
  KF5::PimCommon
)

set_target_properties(KF5KaddressbookImportExport PROPERTIES
    VERSION ${KADDRESSBOOKGRANTLEE_VERSION_STRING}
    SOVERSION ${KADDRESSBOOKGRANTLEE_SOVERSION}
    EXPORT_NAME KaddressbookImportExport
)

install(TARGETS
    KF5KaddressbookImportExport
    EXPORT KF5KaddressbookImportExportTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS} ${LIBRARY_NAMELINK}
)



# ecm_generate_headers(KaddressbookImportExport_CamelCaseprinting_HEADERS
#   HEADER_NAMES
#   GrantleePrint
#   REQUIRED_HEADERS KaddressbookImportExport_printing_HEADERS
#   RELATIVE printing
#   PREFIX KaddressbookImportExport
# )

ecm_generate_pri_file(BASE_NAME KaddressbookImportExport
    LIB_NAME KF5KaddressbookImportExport
    DEPS "Grantlee5" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KaddressbookImportExport
)


# install(FILES
#     ${KaddressbookImportExport_CamelCasewidgets_HEADERS}
#     ${KaddressbookImportExport_CamelCaseformatter_HEADERS}
#     ${KaddressbookImportExport_CamelCaseprinting_HEADERS}
#     DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/KaddressbookImportExport
#     COMPONENT Devel
# )

# install(FILES
#     ${KaddressbookImportExport_HEADERS}
#     ${KaddressbookImportExport_widgets_HEADERS}
#     ${CMAKE_CURRENT_BINARY_DIR}/kaddressbook_grantlee_export.h
#     ${KaddressbookImportExport_formatter_HEADERS}
#     ${KaddressbookImportExport_printing_HEADERS}
#     DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/kaddressbookimportexport
#     COMPONENT Devel
# )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})



