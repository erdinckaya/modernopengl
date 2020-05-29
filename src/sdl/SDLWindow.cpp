#include <SDL2/SDL.h>
#include "SDLWindow.h"

SDLWindow::SDLWindow(unsigned int t_width, unsigned int t_height, const char *t_windowTitle) :
    m_width(t_width),
    m_height(t_height),
    m_windowTitle(t_windowTitle),
    m_window(SDL_CreateWindow(t_windowTitle,
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              t_width,
                              t_height,
                              SDL_WINDOW_OPENGL),
             static_cast<void (&&)(SDL_Window *)>(SDL_DestroyWindow)) {}

/// Fetches window's raw pointer.
SDLWindow::operator SDL_Window *() const {
  return m_window.get();
}
