#ifndef MODERNOPENGL__SDLCONTEXT_H_
#define MODERNOPENGL__SDLCONTEXT_H_
#include "SDLWindow.h"
#include <SDL2/SDL.h>

/// Creates SDL contexts
class SDLContext
{
 public:
  SDLContext(SDLWindow& t_sdlWindow);

  explicit operator SDL_GLContext() const;
 private:
  std::unique_ptr<void, void(*)(SDL_GLContext)> m_context;
};
#endif //MODERNOPENGL__SDLCONTEXT_H_
