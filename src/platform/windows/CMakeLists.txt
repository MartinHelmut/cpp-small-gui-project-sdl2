# Static assets
target_sources(${APP_NAME} PUBLIC
  ${SHARED_STATIC_ASSETS}
  assets/icons/icon.ico
  assets/manifests/app.rc
  assets/manifests/App.manifest)

# Platform dependent sources
target_sources(${APP_NAME} PRIVATE
  platform/windows/Resources.cpp platform/windows/DPIHandler.cpp)

# Use main entry for Windows GUI app.
if (MINGW)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
  # Static link MinGW standard libraries
  set(CMAKE_CXX_STANDARD_LIBRARIES
    "-static-libgcc -static-libstdc++ -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")
else ()
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows /entry:mainCRTStartup")
endif ()

# Copy .dll files on Windows to the target App build folder.
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
  ${PROJECT_SOURCE_DIR}/src/assets
  $<TARGET_FILE_DIR:${APP_NAME}>/../share)

# For distribution:
install(DIRECTORY ${PROJECT_SOURCE_DIR}/src/assets DESTINATION ${CMAKE_INSTALL_DATADIR})
