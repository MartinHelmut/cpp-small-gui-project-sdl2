#include "Application.hpp"

int main() {
  App::Application app{"SmallSDL2App"};
  return static_cast<int>(app.run());
}
