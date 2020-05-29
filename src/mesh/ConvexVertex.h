#ifndef MODERNOPENGL__CONVEXVERTEX_H_
#define MODERNOPENGL__CONVEXVERTEX_H_

#include <glm/glm.hpp>
struct ConvexVertex {
  glm::vec2 position;
  glm::vec3 translation;
  glm::vec3 scale;
  glm::vec3 rotation;
  glm::vec4 color;
  float borderThickness; // [0 - 1.0f]
  float fill; // [0 - 1.0f]
};

#endif //MODERNOPENGL__CONVEXVERTEX_H_
