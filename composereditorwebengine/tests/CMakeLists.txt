PROJECT( composerwebenginehtmleditor )

set(composerhtmlSources
  main.cpp
  composerhtmleditor.cpp
)

add_executable(composerhtmleditor ${composerhtmlSources} )
target_link_libraries(composerhtmleditor KF5::ComposerEditorWebEngine )

install(TARGETS composerhtmleditor ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES
  composerhtmleditorui.rc
  DESTINATION  ${KDE_INSTALL_KXMLGUI5DIR}/composerhtmleditor)

