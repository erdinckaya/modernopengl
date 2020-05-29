#include "Game.h"
#include "../src/ResourceManager.h"
#include "../src/mesh/CircleMesh.h"
#include "../src/mesh/RectangleMesh.h"
#include "../src/mesh/TextMesh.h"
#include "Resources.h"

Game::Game(Renderer &t_render) :
    m_renderer(t_render),
    m_quit(false),
    m_thread([this]() { this->Run(); }) {}


// Game main thread.
void Game::Run() {
  // Create our textures.
  auto images = CreateImages();
  auto last = SDL_GetTicks();
  while (!m_quit) {
    const auto now = SDL_GetTicks();
    const auto kDiffMs = now - last;
    const auto kDiffSec = kDiffMs / 1000.0f;
    last = now;

    // Bind arrow keys to our ball object as an example of key handling.
    auto keyStates = SDL_GetKeyboardState(nullptr);
    const int ballImageIndex = 1;
    const auto diff = 5.0f * kDiffSec;
    if (keyStates[SDL_SCANCODE_LEFT]) {
      images[ballImageIndex].position += glm::vec3(-diff, 0, 0);
    }
    if (keyStates[SDL_SCANCODE_RIGHT]) {
      images[ballImageIndex].position += glm::vec3(diff, 0, 0);
    }
    if (keyStates[SDL_SCANCODE_UP]) {
      images[ballImageIndex].position += glm::vec3(0, diff, 0);
    }
    if (keyStates[SDL_SCANCODE_DOWN]) {
      images[ballImageIndex].position += glm::vec3(0, -diff, 0);
    }

    // Create render data of our objects such as translate, rotation, and scale.
    // After that you have to create render data which contains shader and vertices of object also texture id as well.
    // Render data feeds the renderer to render objects with batch rendering.
    std::vector<RenderData> dataList;
    for (auto &image : images) {
      auto model = glm::mat4(1.0f);
      model = glm::translate(model, image.position);
      model = glm::rotate(model, glm::radians(image.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, glm::radians(image.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
      model = glm::rotate(model, glm::radians(image.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
      model = glm::scale(model, image.scale);
      image.mesh.SetModel(model);
      dataList.emplace_back(image.mesh.Vertices(), ShaderType::Texture, image.texture.TextureId());
    }

    // Build basic rectangle mesh
    auto mesh = RectangleMesh()
        .SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f))
        .SetScale(glm::vec3(1.0f))
        .SetRotation(glm::vec3(0.0f))
        .SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f))
        .FetFill(0.0f)
        .SetBorderThickness(0.1f)
        .SetSortingOrder(10)
        .Build();

    dataList.emplace_back(mesh.Vertices(), ShaderType::Rectangle, 0);

    // Build basic circle mesh
    auto cMesh = CircleMesh()
        .SetTranslation(glm::vec3(0.0f, 0.0f, 0.0f))
        .SetScale(glm::vec3(2.5f))
        .SetRotation(glm::vec3(0.0f))
        .SetColor(glm::vec4(1.0f, 0.0f, 1.0f, 0.5f))
        .FetFill(1.0f)
        .SetBorderThickness(0.1f)
        .SetSortingOrder(11)
        .Build();

    dataList.emplace_back(cMesh.Vertices(), ShaderType::Circle, 0);

    // Render text.
    // In order to render text we need to create every character's mesh. Therefore we have to encapsulate all characters
    // into a single struct which is TextMesh. Note that since all system is using batch rendering creating same character
    // meshes does not make any difference in terms of performance except creating dump data by user.
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, 1.0f, 0.0f));
    auto textMesh = TextMesh()
        .SetText(CreateAlphabet())
        .SetSortingOrder(20)
        .SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f))
        .SetModel(model)
        .Build();

    // Since texts are like image textures TextMesh generates texture meshes.
    // Feed renderer with texture meshes.
    const std::vector<TextureMesh> &charMeshes = textMesh.CharMeshes();
    for (const auto &charMesh : charMeshes) {
      dataList.emplace_back(charMesh.Vertices(), ShaderType::Text, charMesh.TextureId());
    }

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-3.0f, 0.7f, 0.0f));
    auto textMesh1 = TextMesh()
        .SetText(CreateAlphabet())
        .SetSortingOrder(20)
        .SetColor({0.3f, 0.7f, 0.8f, 1.0f})
        .SetModel(model)
        .Build();

    const std::vector<TextureMesh> &charMeshes1 = textMesh1.CharMeshes();
    for (const auto &charMesh : charMeshes1) {
      dataList.emplace_back(charMesh.Vertices(), ShaderType::Text, charMesh.TextureId());
    }

    m_renderer.AddBatch(std::move(dataList));
  }
}
std::array<GameObject, 4> Game::CreateImages() {
  // Get resources manager instance, not that it is singleton and it cannot be copiable, so that you have to
  // use it with reference.
  ResourceManager &resourceManager = ResourceManager::instance();
  // Texture is not copiable, since its life time is bounded to actual texture which is stored inside of resource manager.
  // Instead of using shared ptr we can use pass it through reference it is more efficient.
  const Texture &backgroundTexture = resourceManager.GetTexture(TextureType::Background);
  // Give texture's actual size but please note that size will be used to preserve ratio of texture.
  // If you want to change the size of texture you should use scale. Secondly give texture sorting order which
  // will be assigned into z value of image and it helps to sort render order.
  TextureMesh backgroundMesh(backgroundTexture.Size(), 1.0f);

  const Texture &ballTexture = resourceManager.GetTexture(TextureType::Ball);
  TextureMesh ballMesh(ballTexture.Size(), 3.0f);

  const Texture &paddleTexture = resourceManager.GetTexture(TextureType::Paddle);
  TextureMesh paddleMesh(paddleTexture.Size(), 2.0f);

  // Create our game objects.
  constexpr float ballScale = 0.5f;
  constexpr float paddleY = 2.7f;
  constexpr glm::vec3 paddleScale = glm::vec3(1.8f, 1.0f, 1.0f);
  std::array<GameObject, 4> images = {
      GameObject(backgroundTexture, backgroundMesh, glm::vec3(0.0f), glm::vec3(8, 12, 1)),
      GameObject(ballTexture, ballMesh, glm::vec3(0.0f), glm::vec3(ballScale, ballScale, 1)),
      GameObject(paddleTexture, paddleMesh, glm::vec3(0.0f, paddleY, 0.0f), paddleScale),
      GameObject(paddleTexture, paddleMesh, glm::vec3(0.0f, -paddleY, 0.0f), paddleScale)
  };

  return images;
}
void Game::Join() {
  m_thread.join();
}
void Game::Quit() {
  m_quit = true;
}
std::string Game::CreateAlphabet() {
  char alphabet[53];
  for (int i = 0; i < 26; ++i) {
    alphabet[i] = static_cast<char>(65 + i);
    alphabet[i + 26] = static_cast<char>(97 + i);
  }

  alphabet[52] = '\0';
  return std::string(alphabet);
}
