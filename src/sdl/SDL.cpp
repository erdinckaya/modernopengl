#include <iostream>
#include <SDL2/SDL.h>
#include "SDL.h"

SDL::SDL(int t_flags) {
  if (SDL_Init(t_flags) < 0) {
    std::cerr << "Could not initialise SDL: " << SDL_GetError() << std::endl;
    exit(-1);
  }

  // Configuration
#ifdef __APPLE__
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
#endif
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
//  SDL_SetRelativeMouseMode(SDL_TRUE);
}
SDL::~SDL() {
  SDL_Quit();
}
