include(FetchContent)

FetchContent_Declare(
  SDL2
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
  GIT_TAG release-2.30.1
)

FetchContent_Declare(
  SDL2_ttf
  GIT_REPOSITORY "https://github.com/libsdl-org/SDL_ttf.git"
  GIT_TAG release-2.22.0
)

# For SDL2 to be able to override options
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(SDL2_DISABLE_SDL2MAIN ON)
set(SDL2TTF_INSTALL OFF)

if (MINGW)
  set(SDL2TTF_VENDORED TRUE)
endif ()

FetchContent_MakeAvailable(SDL2 SDL2_ttf)
