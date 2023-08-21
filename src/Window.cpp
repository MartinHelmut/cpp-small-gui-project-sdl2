#include "Window.hpp"

#include <string>

#include "DPIHandler.hpp"

namespace App {

Window::Window(const Settings& settings) {
  const WindowSize size{DPIHandler::get_dpi_aware_window_size(settings)};

  m_window = SDL_CreateWindow(std::string(settings.title).c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      size.width,
      size.height,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  m_renderer =
      SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  if (m_renderer == nullptr) {
    SDL_Log("Error creating SDL_Renderer!");
    return;
  }

  DPIHandler::set_render_scale(m_renderer);

  // Show the currently used render backend
  SDL_RendererInfo info;
  SDL_GetRendererInfo(m_renderer, &info);
  SDL_Log("Current SDL_Renderer: %s", info.name);
}

Window::~Window() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
}

SDL_Renderer* Window::get_native_renderer() const {
  return m_renderer;
}

SDL_Window* Window::get_native_window() const {
  return m_window;
}

}  // namespace App
