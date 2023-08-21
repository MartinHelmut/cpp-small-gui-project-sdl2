#include "Application.hpp"

#include "DPIHandler.hpp"
#include "Resources.hpp"

namespace App {

Application::Application(std::string_view title) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
    SDL_Log("Error: %s\n", SDL_GetError());
    m_exit_status = ExitStatus::FAILURE;
  }

  TTF_Init();

  m_window = std::make_unique<Window>(Window::Settings{title});

  // Font setup
  const std::string font_path{Resources::font_path("Manrope.ttf").generic_string()};
  m_font = TTF_OpenFont(font_path.c_str(), 0);
  DPIHandler::set_font_size(m_font, 18.0F);
  TTF_SetFontHinting(m_font, TTF_HINTING_LIGHT_SUBPIXEL);
}

Application::~Application() {
  TTF_CloseFont(m_font);
  TTF_Quit();
  SDL_Quit();
}

ExitStatus App::Application::run() {
  m_running = m_exit_status != ExitStatus::FAILURE;

  while (m_running) {
    SDL_Event event{};
    while (SDL_PollEvent(&event) == 1) {
      if (event.type == SDL_QUIT) {
        stop();
      }
    }

    SDL_SetRenderDrawColor(m_window->get_native_renderer(), 50, 50, 50, 255);
    SDL_RenderClear(m_window->get_native_renderer());

    // Rendering
    on_update();

    SDL_RenderPresent(m_window->get_native_renderer());
  }

  return m_exit_status;
}

void App::Application::stop() {
  m_running = false;
}

void Application::on_update() {
  // Example SDL2 code

  constexpr int window_padding{10};
  constexpr SDL_Color background_color{255, 255, 255, 255};

  int window_width{};
  int window_height{};
  SDL_GetWindowSize(m_window->get_native_window(), &window_width, &window_height);

  const SDL_Rect rect{window_padding,
      window_padding,
      window_width - window_padding * 2,
      window_height - window_padding * 2};

  SDL_SetRenderDrawColor(m_window->get_native_renderer(), 255, 255, 255, 255);
  SDL_RenderDrawRect(m_window->get_native_renderer(), &rect);
  SDL_SetRenderDrawColor(m_window->get_native_renderer(), 0, 0, 0, 255);

  SDL_Surface* surface{TTF_RenderText_Blended(m_font, "Small SDL2 App", background_color)};
  SDL_Texture* texture{SDL_CreateTextureFromSurface(m_window->get_native_renderer(), surface)};

  int text_width{};
  int text_height{};
  SDL_QueryTexture(texture, nullptr, nullptr, &text_width, &text_height);

  // Position the text at the center
  const SDL_Rect text_rect{((window_width / 2) - (text_width / 2)),
      ((window_height / 2) - (text_height / 2)),
      text_width,
      text_height};
  SDL_RenderCopy(m_window->get_native_renderer(), texture, nullptr, &text_rect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

}  // namespace App
