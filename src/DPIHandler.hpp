#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include "Window.hpp"

namespace App {

struct WindowSize {
  int width;
  int height;
};

class DPIHandler {
 public:
  [[nodiscard]] static float get_scale();

  [[nodiscard]] static WindowSize get_dpi_aware_window_size(const Window::Settings& settings);

  static void set_render_scale(SDL_Renderer* renderer);
  static void set_font_size(TTF_Font* font, float size);
};

}  // namespace App
