#include "SDLContext.h"

SDLContext::SDLContext(SDLWindow& t_sdlWindow)
    : m_context(SDL_GL_CreateContext(t_sdlWindow), static_cast<void (&&)(SDL_GLContext)>(SDL_GL_DeleteContext))
{
}

SDLContext::operator SDL_GLContext() const
{
  return m_context.get();
}