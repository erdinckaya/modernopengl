#ifndef MODERNOPENGL__GAME_H_
#define MODERNOPENGL__GAME_H_
#include <thread>
#include <atomic>
#include "../src/render/Renderer.h"
#include "GameObject.h"

class Game {
 public:
  explicit Game(Renderer &t_render);

  void Quit();
  void Join();

 private:
  void Run();
  static std::array<GameObject, 4> CreateImages();
  static std::string CreateAlphabet();

  Renderer &m_renderer;

  std::atomic<bool> m_quit;
  std::thread m_thread;
};

#endif //MODERNOPENGL__GAME_H_
