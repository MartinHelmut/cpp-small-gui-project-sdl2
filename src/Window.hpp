#pragma once

#include <string_view>

#include "SDL.h"

namespace App {

class Window {
 public:
  struct Settings {
    std::string_view title;
    int width{640};
    int height{360};
  };

  explicit Window(const Settings& settings);
  ~Window();

  Window(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window other) = delete;
  Window& operator=(Window&& other) = delete;

  [[nodiscard]] SDL_Renderer* get_native_renderer() const;
  [[nodiscard]] SDL_Window* get_native_window() const;

 private:
  SDL_Window* m_window{nullptr};
  SDL_Renderer* m_renderer{nullptr};
};

}  // namespace App
