#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <memory>

class SDLWindow {
 public:
  explicit SDLWindow(unsigned int t_width, unsigned int t_height, const char* t_windowTitle);

  operator SDL_Window *() const;

 private:
  unsigned int m_width;
  unsigned int m_height;
  std::string m_windowTitle;

  std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> m_window;
};