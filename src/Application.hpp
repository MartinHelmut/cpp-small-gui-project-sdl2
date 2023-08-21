#pragma once

#include <memory>
#include <string_view>

#include "SDL.h"
#include "SDL_ttf.h"
#include "Window.hpp"

namespace App {

enum class ExitStatus : int { SUCCESS = 0, FAILURE = 1 };

class Application {
 public:
  explicit Application(std::string_view title);
  ~Application();

  Application(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application other) = delete;
  Application& operator=(Application&& other) = delete;

  [[nodiscard]] ExitStatus run();
  void stop();
  void on_update();

 private:
  ExitStatus m_exit_status{ExitStatus::SUCCESS};
  std::unique_ptr<Window> m_window{nullptr};
  TTF_Font* m_font{nullptr};

  bool m_running{true};
};

}  // namespace App
