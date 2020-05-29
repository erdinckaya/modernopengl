#ifndef MODERNOPENGL__WINDOW_H_
#define MODERNOPENGL__WINDOW_H_

#include "../sdl/SDL.h"
#include "../sdl/SDLWindow.h"

class Window {
 public:
  Window(unsigned int t_width, unsigned int t_height, const char* t_windowTitle);

  unsigned int Width() const;
  void SetWidth(unsigned int t_width);
  unsigned int Height() const;
  void SetHeight(unsigned int t_height);
  float AspectRatio() const;

  SDLWindow& GetWindow();

 private:
  SDL m_sdl;
  SDLWindow m_window;
  unsigned int m_width;
  unsigned int m_height;
};

#endif //MODERNOPENGL__WINDOW_H_
