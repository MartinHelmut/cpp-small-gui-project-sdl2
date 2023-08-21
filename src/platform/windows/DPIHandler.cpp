#include "DPIHandler.hpp"

namespace App {

float DPIHandler::get_scale() {
  constexpr int display_index{0};
  const float default_dpi{96.0F};
  float dpi{default_dpi};

  SDL_GetDisplayDPI(display_index, nullptr, &dpi, nullptr);

  return dpi / default_dpi;
}

WindowSize DPIHandler::get_dpi_aware_window_size(const Window::Settings& settings) {
  const float scale{DPIHandler::get_scale()};
  const int width{static_cast<int>(static_cast<float>(settings.width) * scale)};
  const int height{static_cast<int>(static_cast<float>(settings.height) * scale)};
  return {width, height};
}

void DPIHandler::set_render_scale([[maybe_unused]] SDL_Renderer* renderer) {
  // Do nothing on Windows
}

void DPIHandler::set_font_size(TTF_Font* font, float size) {
  constexpr int display_index{0};
  float hdpi{};
  float vdpi{};
  SDL_GetDisplayDPI(display_index, nullptr, &hdpi, &vdpi);

  TTF_SetFontSizeDPI(font,
      static_cast<int>(size / get_scale()),
      static_cast<unsigned int>(hdpi),
      static_cast<unsigned int>(vdpi));
}

}  // namespace App
