include(FetchContent)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
  GIT_TAG release-2.28.4
)

option(SDL2_DISABLE_SDL2MAIN "Disable building/installation of SDL2main" ON)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
  SDL2_ttf
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
  GIT_TAG release-2.20.2
)

set(SDL2TTF_INSTALL OFF)
FetchContent_MakeAvailable(SDL2_ttf)
