
#include "../src/components/Texture.h"
#include "../src/components/Camera.h"
#include "../src/components/Window.h"
#include "Game.h"
#include "../src/ResourceManager.h"
#include "Resources.h"

#include <SDL2/SDL.h>

void HandleCameraMove(Camera &camera, float deltaTime);
int main(int argc, char *argv[]) {

  // Create configs and assets.
  constexpr unsigned int ScreenWidth = 800;
  constexpr unsigned int ScreenHeight = 600;
  // First create window by requesting from operating system.
  // Window is created by using SDL2 since SDL2 supports almost all platforms, it is easy to create
  // window with SDL2.
  Window window(ScreenWidth, ScreenHeight, "Modern Opengl");
  // Create camera.
  Camera camera(glm::vec3(0.0f, 0.0f, 7.2f));
  // Create resource manager. Resource manager is singleton class that you can reach from everywhere.
  // ResourceManager initialize all resources and responsible from their life time.
  ResourceManager &resourceManager = ResourceManager::instance();
  // Create OpenGL context and our renderer class. It takes camera and window. It uses window to bind opengl contex.
  Renderer renderer(window, camera);
  // Load our assets.
  resourceManager.LoadResources(Resources::GetTexturePaths(), Resources::GetShaderPaths(), Resources::GetFontPaths());
  // Prepare batches to render all render objects.
  renderer.CreateBatches();

  // When assets and window are ready Game can start.
  std::cout << "Main is ready" << std::endl;
  // Pass renderer to game object to give the ability to draw objects.
  // Game has its own thread and it starts automatically when a game object is initialized.
  Game game(renderer);

  // Classic render loop.
  // Note that render loop is working in main thread. Since opengl context and
  // SDL window must be in the same tread in Macos so that it is easy to use render thread
  // in main thread and game thread in another thread.
  auto now = SDL_GetTicks() / 1000.0f;
  auto lastFrame = now;
  bool quit = false;
  while (!quit) {
    now = SDL_GetTicks() / 1000.0f;
    auto deltaTime = now - lastFrame;
    lastFrame = now;

    // Handles camera move.
    HandleCameraMove(camera, deltaTime);

    // Check SDL events.
    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent)) {
      switch (windowEvent.type) {
        case SDL_QUIT:quit = true;
          break;
        case SDL_KEYDOWN:
          if (windowEvent.key.keysym.sym == SDLK_ESCAPE) {
            quit = true;
          }
          break;
      }
    }

    // Render all objects.
    renderer.Draw();
  }

// End the game.
  game.Quit();
// Wait to deallocate resources.
  game.Join();

  return 0;
}
void HandleCameraMove(Camera &camera, float deltaTime) {
  auto keyStates = SDL_GetKeyboardState(nullptr);

  //continuous-response keys
  if (keyStates[SDL_SCANCODE_W]) {
    camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
  }
  if (keyStates[SDL_SCANCODE_S]) {
    camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
  }
  if (keyStates[SDL_SCANCODE_A]) {
    camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
  }
  if (keyStates[SDL_SCANCODE_D]) {
    camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
  }
}
