#include "Window.h"
Window::Window(unsigned int t_width, unsigned int t_height, const char *t_windowTitle) :
    m_width(t_width),
    m_height(t_height),
    m_sdl(SDL_INIT_VIDEO),
    m_window(t_width, t_height, t_windowTitle) {

}


unsigned int Window::Width() const {
  return m_width;
}
void Window::SetWidth(unsigned int t_width) {
  m_width = t_width;
}
unsigned int Window::Height() const {
  return m_height;
}
void Window::SetHeight(unsigned int t_height) {
  m_height = t_height;
}
float Window::AspectRatio() const {
  return static_cast<float>(Width()) / static_cast<float>(Height());
}
SDLWindow& Window::GetWindow() {
  return m_window;
}
