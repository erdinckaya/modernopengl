#ifndef MODERNOPENGL__TEXTUREVERTEX_H_
#define MODERNOPENGL__TEXTUREVERTEX_H_

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

struct TextureVertex
{
  glm::vec3 position;
  glm::vec2 texCoords;
  glm::vec4 color;
  float index = 0;
};

#endif //MODERNOPENGL__TEXTUREVERTEX_H_
