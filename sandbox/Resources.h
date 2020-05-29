#ifndef MODERNOPENGL_SANDBOX_RESOURCES_H_
#define MODERNOPENGL_SANDBOX_RESOURCES_H_
#include "../vendor/enum.h"

// Add resources here.
BETTER_ENUM(TextureType, unsigned int, Background, Ball, Paddle, BallParticle)
BETTER_ENUM(FontType, unsigned int, Fontana)

namespace Resources {
static std::array<const char *, ShaderType::_size() * 2> GetShaderPaths() {
  std::array<const char *, ShaderType::_size() * 2> shaderPaths{};
  shaderPaths[ShaderType::Texture * 2] = "../resources/shaders/core.vert";
  shaderPaths[ShaderType::Texture * 2 + 1] = "../resources/shaders/core.frag";
  shaderPaths[ShaderType::Rectangle * 2] = "../resources/shaders/rect.vert";
  shaderPaths[ShaderType::Rectangle * 2 + 1] = "../resources/shaders/rect.frag";
  shaderPaths[ShaderType::Circle * 2] = "../resources/shaders/circle.vert";
  shaderPaths[ShaderType::Circle * 2 + 1] = "../resources/shaders/circle.frag";
  shaderPaths[ShaderType::Text * 2] = "../resources/shaders/text.vert";
  shaderPaths[ShaderType::Text * 2 + 1] = "../resources/shaders/text.frag";
  return shaderPaths;
}

static std::array<const char *, TextureType::_size()> GetTexturePaths() {
  std::array<const char *, TextureType::_size()> texturePaths{};
  texturePaths[TextureType::Background] = "../resources/textures/Background.png";
  texturePaths[TextureType::Ball] = "../resources/textures/Ball.png";
  texturePaths[TextureType::Paddle] = "../resources/textures/Paddle.jpeg";
  texturePaths[TextureType::BallParticle] = "../resources/textures/BallParticle.png";
  return texturePaths;
}

static std::array<const char *, FontType::_size()> GetFontPaths() {
  std::array<const char *, FontType::_size()> fontPaths{};
  fontPaths[FontType::Fontana] = "../resources/fonts/Fontana.ttf";
  return fontPaths;
}
}

#endif //MODERNOPENGL_SANDBOX_RESOURCES_H_
