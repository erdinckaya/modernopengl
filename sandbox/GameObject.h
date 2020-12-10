#ifndef MODERNOPENGL__GAMEOBJECT_H_
#define MODERNOPENGL__GAMEOBJECT_H_

#include "../src/mesh/TextureMesh.h"
#include "../src/components/Texture.h"
#include <glm/glm.hpp>
#include <utility>

struct State {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotation;
};

enum class StateType {
    Previous = 0,
    Current = 1
};

struct GameObject {

  explicit GameObject(const Texture &texture,
                      TextureMesh mesh,
                      glm::vec3 pos = glm::vec3(0.0f),
                      glm::vec3 scale = glm::vec3(1.0f),
                      glm::vec3 rotate = glm::vec3(0.0f))
      : texture(texture), mesh(std::move(mesh)), state{{{}, {pos, scale, rotate}}} {}
  const Texture &texture;
  TextureMesh mesh;
  std::array<State, 2> state;
};

#endif //MODERNOPENGL__GAMEOBJECT_H_
