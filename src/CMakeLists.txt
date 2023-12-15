set(APP_NAME SmallSDL2App)

add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE
  Main.cpp
  Application.cpp Application.hpp
  Window.cpp Window.hpp
  Resources.hpp DPIHandler.hpp)

# Assets for all platforms
set(SHARED_STATIC_ASSETS assets/fonts/Manrope.ttf)

# General target installation settings
install(TARGETS ${APP_NAME}
  BUNDLE DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

# Settings for packaging per platform
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  include(platform/windows/CMakeLists.txt)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  include(platform/linux/CMakeLists.txt)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  include(platform/darwin/CMakeLists.txt)
endif ()

target_include_directories(${APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${APP_NAME} PRIVATE cxx_std_20)
target_link_libraries(${APP_NAME}
  PRIVATE project_warnings
  PUBLIC SDL2::SDL2 SDL2_ttf::SDL2_ttf)
