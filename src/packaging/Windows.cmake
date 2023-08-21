# Use main entry for Windows GUI app.
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /entry:mainCRTStartup")

# Copy .dll files on Windows/Linux to the target App build folder.
# For development:
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:SDL2::SDL2>
  $<TARGET_FILE_DIR:${APP_NAME}>)
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:SDL2_ttf::SDL2_ttf>
  $<TARGET_FILE_DIR:${APP_NAME}>)

# For distribution:
install(FILES $<TARGET_FILE:SDL2::SDL2> DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES $<TARGET_FILE:SDL2_ttf::SDL2_ttf> DESTINATION ${CMAKE_INSTALL_BINDIR})

# Copy assets into app bundle
# For development:
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  ../assets
  $<TARGET_FILE_DIR:${APP_NAME}>/../share)

# For distribution:
install(DIRECTORY ../assets DESTINATION ${CMAKE_INSTALL_DATADIR})
