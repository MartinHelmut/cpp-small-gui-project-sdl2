# Static assets
set(MACOSX_STATIC_ASSETS
  ${SHARED_STATIC_ASSETS}
  assets/icons/icon.icns)
set_source_files_properties(${MACOSX_STATIC_ASSETS}
  PROPERTIES MACOSX_PACKAGE_LOCATION ${CMAKE_INSTALL_DATADIR})
target_sources(${APP_NAME} PUBLIC ${MACOSX_STATIC_ASSETS})

# Platform dependent sources
target_sources(${APP_NAME} PRIVATE
  platform/darwin/Resources.cpp platform/darwin/DPIHandler.cpp)

# Get dynamic SDL2 lib into Frameworks folder in app bundle.
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  $<TARGET_FILE:SDL2::SDL2>
  $<TARGET_FILE_DIR:${APP_NAME}>/../Frameworks/$<TARGET_FILE_NAME:SDL2::SDL2>)

# Get dynamic SDL2_ttf lib into Frameworks folder in app bundle.
# Though, in this case the whole folder content will be copied to retrieve possible
# alias names for SDL2_ttf.
add_custom_command(TARGET ${APP_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  $<TARGET_FILE_DIR:SDL2_ttf::SDL2_ttf>/
  $<TARGET_FILE_DIR:${APP_NAME}>/../Frameworks/)

# For distribution without XCode:
if (NOT "${CMAKE_GENERATOR}" STREQUAL "Xcode")
  install(FILES $<TARGET_FILE:SDL2::SDL2> DESTINATION $<TARGET_FILE_DIR:${APP_NAME}>/../Frameworks/)
  install(FILES $<TARGET_FILE:SDL2_ttf::SDL2_ttf> DESTINATION $<TARGET_FILE_DIR:${APP_NAME}>/../Frameworks/)
endif ()

# macOS package settings
string(TIMESTAMP CURR_YEAR "%Y")
set_target_properties(${APP_NAME} PROPERTIES
  INSTALL_RPATH @executable_path/../Frameworks
  RESOURCE "${MACOSX_STATIC_ASSETS}"
  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/assets/manifests/Info.plist"
  MACOSX_BUNDLE_BUNDLE_VERSION "${BUILD_VERSION}"
  MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
  MACOSX_BUNDLE_GUI_IDENTIFIER "${PROJECT_COMPANY_NAMESPACE}.${CMAKE_PROJECT_NAME}"
  XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${PROJECT_COMPANY_NAMESPACE}.${CMAKE_PROJECT_NAME}"
  MACOSX_BUNDLE_COPYRIGHT "(c) ${CURR_YEAR} ${PROJECT_COMPANY_NAME}"
  XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
