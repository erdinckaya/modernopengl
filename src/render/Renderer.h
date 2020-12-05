#ifndef MODERNOPENGL__RENDERER_H_
#define MODERNOPENGL__RENDERER_H_



#include <glm/glm.hpp>
#include <mutex>
#include <queue>
#include "../components/Window.h"
#include "../sdl/SDLContext.h"
#include "../batch/BatchInterface.h"
#include "../util/Types.h"
#include "../util/RenderQueue.h"
#include "RenderData.h"
#include "../components/Camera.h"
#include "../components/Texture.h"

class Renderer {

 public:
  explicit Renderer(Window& t_window, const Camera& t_camera);

  void AddBatch(std::vector<RenderData>&& t_batchData);
  void Draw();
  void CreateBatches();

 private:
  void SwapWindow();
  static GLenum GlCheckErrorHelper(const char *t_file, int t_line);

  Window& m_window;
  const Camera& m_camera;
  SDLContext m_context;
  std::unique_ptr<BatchInterface> m_batches[ShaderType::_size()];

  //RenderQueue m_BatchQueue;
  std::mutex mMutex;
  std::vector<RenderData> mCurrent;
  std::vector<RenderData> mNext;
  int sizeQ{0};

};

#endif //MODERNOPENGL__RENDERER_H_
