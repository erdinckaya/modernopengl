#ifndef MODERNOPENGL__BATCHINTERFACE_H_
#define MODERNOPENGL__BATCHINTERFACE_H_
#include <vector>
// Base class for batch rendering.
struct BatchInterface {
  typedef unsigned int GLuint;

  virtual ~BatchInterface() = default;
  virtual void Draw(const glm::mat4 &t_projectView) = 0;
  virtual void Add(GLuint t_textureId, std::vector<float> &t_vertices, const glm::mat4 &t_pvm) = 0;
};

#endif //MODERNOPENGL__BATCHINTERFACE_H_
