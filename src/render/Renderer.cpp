#include "Renderer.h"
#include "../batch/TextureBatch.h"
#include "../ResourceManager.h"
#include "../mesh/TextureMesh.h"
#include "../batch/ConvexBatch.h"
#include <GL/glew.h>

GLenum Renderer::GlCheckErrorHelper(const char *t_file, int t_line) {
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR) {
    std::string error;
    switch (errorCode) {
      case GL_INVALID_ENUM: error = "INVALID_ENUM";
        break;
      case GL_INVALID_VALUE: error = "INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION: error = "INVALID_OPERATION";
        break;
      case GL_STACK_OVERFLOW: error = "STACK_OVERFLOW";
        break;
      case GL_STACK_UNDERFLOW: error = "STACK_UNDERFLOW";
        break;
      case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION";
        break;
      default:break;
    }
    std::cout << error << " | " << t_file << " (" << t_line << ")" << std::endl;
  }
  return errorCode;
}
#define glCheckError() Renderer::GlCheckErrorHelper(__FILE__, __LINE__)

Renderer::Renderer(Window &t_window, const Camera &t_camera) :
    m_window(t_window), m_camera(t_camera),
    m_context(m_window.GetWindow()) {

  // Init glew.
  glewInit();
  // Init view port.
  glViewport(0, 0, m_window.Width(), m_window.Height());



  // During init, enable debug output
  glEnable(GL_DEBUG_OUTPUT);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Disable vsync
  SDL_GL_SetSwapInterval(0);

  std::cout << "OpenGL version " << glGetString(GL_VERSION) << std::endl;
}

void Renderer::SwapWindow() {
  SDL_GL_SwapWindow(m_window.GetWindow());
}
void Renderer::CreateBatches() {
  for (auto &type : ShaderType::_values()) {
    switch (type) {
      case ShaderType::Text:
      case ShaderType::Texture: {
        m_batches[type] = std::make_unique<TextureBatch>(ResourceManager::instance().GetShader(type));
        break;
      }
      case ShaderType::Circle:
      case ShaderType::Rectangle: {
        m_batches[type] = std::make_unique<ConvexBatch>(ResourceManager::instance().GetShader(type));
        break;
      }
    }
  }
}
void Renderer::AddBatch(std::vector<RenderData> &&t_batchData) {
    std::lock_guard <std::mutex> guard(mMutex);
    mNext = t_batchData;
    sizeQ++;
}

template<typename Mutex, typename Callback, typename ...Args>
auto ScopedLock(Mutex& mutex, Callback&& callback, Args&& ...args) {
    std::lock_guard <Mutex> guard(mutex);
    return callback(std::forward<Args>(args)...);
}

void Renderer::Draw() {
    ScopedLock(mMutex, [](auto& current, auto& next) {
        current = next;
    }, mCurrent, mNext);

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  const auto projection = glm::perspective(glm::radians(m_camera.Zoom()), m_window.AspectRatio(), 0.1f, 100.0f);
  const auto view = m_camera.ViewMatrix();
  const auto pvm = projection * view;

  for (auto batchType : ShaderType::_values()) {
    for (auto &data : mCurrent) {
      if (batchType == data.batchType) {
        m_batches[data.batchType]->Add(data.textureId, data.vertices, pvm);
      }
    }
    m_batches[batchType]->Draw(pvm);
  }

  glCheckError();
  SwapWindow();
}

