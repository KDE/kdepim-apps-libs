add_definitions(-DTRANSLATION_DOMAIN=\"libcomposereditorwebengine\")

set(libcomposereditor_webengine_SRCS
    composerwebengine.cpp
)

ecm_qt_declare_logging_category(libcomposereditor_webengine_SRCS HEADER composereditorwebengine_debug.h IDENTIFIER COMPOSEREDITORNG_LOG CATEGORY_NAME log_composereditorwebengine)


add_library(KF5ComposerEditorWebEngine ${libcomposereditor_webengine_SRCS})
generate_export_header(KF5ComposerEditorWebEngine BASE_NAME composereditorwebengine)
add_library(KF5::ComposerEditorWebEngine ALIAS KF5ComposerEditorWebEngine)

target_link_libraries(KF5ComposerEditorWebEngine
 PRIVATE
   KF5::PimTextEdit
   KF5::SonnetCore
   KF5::PimCommon
   KF5::KIOWidgets
   KF5::XmlGui
   KF5::Completion
   Qt5::WebEngine
   Qt5::WebEngineWidgets
)

target_include_directories(KF5ComposerEditorWebEngine INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/ComposerEditorWebEngine/;${KDE_INSTALL_INCLUDEDIR_KF5}/composereditorwebengine>")
target_include_directories(KF5ComposerEditorWebEngine PUBLIC "$<BUILD_INTERFACE:${composereditorwebengine_SOURCE_DIR}/src;${composereditorwebengine_BINARY_DIR}/src>")


set_target_properties(KF5ComposerEditorWebEngine PROPERTIES
    VERSION ${COMPOSEREDITORWEBENGINE_VERSION_STRING}
    SOVERSION ${COMPOSEREDITORWEBENGINE_SOVERSION}
    EXPORT_NAME ComposerEditorWebEngine
)

install(TARGETS
    KF5ComposerEditorWebEngine
    EXPORT KF5ComposerEditorWebEngineTargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS} ${LIBRARY_NAMELINK}
)

# ecm_generate_headers(composereditorwebengine_CamelCase_HEADERS
#   HEADER_NAMES
#   ComposerEditor
#   ComposerView
#   REQUIRED_HEADERS composereditorwebengine_HEADERS
#   PREFIX ComposerEditorWebEngine
# )


ecm_generate_pri_file(BASE_NAME ComposerEditorWebEngine
    LIB_NAME KF5ComposerEditorWebEngine
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/ComposerEditorWebEngine
)


install(FILES
    ${composereditorwebengine_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/ComposerEditorWebEngine
    COMPONENT Devel
)

install(FILES
    ${composereditorwebengine_HEADERS}
    ${CMAKE_CURRENT_BINARY_DIR}/composereditorwebengine_export.h
    ${composereditorwebengine_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF5}/composereditorwebengine
    COMPONENT Devel
)
install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})



install( FILES data/composereditorinitialhtml DESTINATION  ${KDE_INSTALL_DATADIR}/composereditorwebengine )


