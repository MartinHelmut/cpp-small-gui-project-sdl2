set(APP_NAME SmallSDL2App)

add_executable(${APP_NAME}
  Main.cpp
  Application.cpp Application.hpp
  Window.cpp Window.hpp
  Resources.hpp DPIHandler.hpp)

target_include_directories(${APP_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(${APP_NAME} PRIVATE cxx_std_20)
target_link_libraries(${APP_NAME}
  PRIVATE project_warnings
  PUBLIC SDL2::SDL2 SDL2_ttf::SDL2_ttf)
