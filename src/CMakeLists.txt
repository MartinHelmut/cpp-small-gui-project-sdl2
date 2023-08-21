set(APP_NAME SmallSDL2App)

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE
  Main.cpp
  Application.cpp Application.hpp
  Window.cpp Window.hpp
  Resources.hpp DPIHandler.hpp)

# Assets for all platforms
set(SHARED_STATIC_ASSETS assets/fonts/Manrope.ttf)

# Platform specific static assets
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_sources(${APP_NAME} PUBLIC
    ${SHARED_STATIC_ASSETS}
    assets/icons/icon.ico
    assets/manifests/app.rc
    assets/manifests/App.manifest)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(MACOSX_STATIC_ASSETS
    ${SHARED_STATIC_ASSETS}
    assets/icons/icon.icns)
  set_source_files_properties(${MACOSX_STATIC_ASSETS}
    PROPERTIES MACOSX_PACKAGE_LOCATION ${CMAKE_INSTALL_DATADIR})
  target_sources(${APP_NAME} PUBLIC ${MACOSX_STATIC_ASSETS})
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_sources(${APP_NAME} PRIVATE ${SHARED_STATIC_ASSETS})
endif ()

# Define set of OS specific files to include
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_sources(${APP_NAME} PRIVATE
    platform/windows/Resources.cpp platform/windows/DPIHandler.cpp)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_sources(${APP_NAME} PRIVATE
    platform/macos/Resources.cpp platform/macos/DPIHandler.cpp)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_sources(${APP_NAME} PRIVATE
    platform/linux/Resources.cpp platform/linux/DPIHandler.cpp)
endif ()

# General target installation settings
install(TARGETS ${APP_NAME}
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Settings for packaging per platform
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  include(packaging/Windows.cmake)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  include(packaging/Linux.cmake)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  include(packaging/Darwin.cmake)
endif ()

target_include_directories(${APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${APP_NAME} PRIVATE cxx_std_20)
target_link_libraries(${APP_NAME}
  PRIVATE project_warnings
  PUBLIC SDL2::SDL2 SDL2_ttf::SDL2_ttf)
