#ifndef MODERNOPENGL__CONVEXBATCH_H_
#define MODERNOPENGL__CONVEXBATCH_H_
#include <vector>
#include <glm/glm.hpp>

#include "../components/Shader.h"
#include "BatchInterface.h"

class ConvexBatch : public BatchInterface {
 public:
  explicit ConvexBatch(const Shader &t_shader);

  void Add(GLuint t_textureId, std::vector<float> &t_vertices, const glm::mat4 &t_pvm) override;
  void Draw(const glm::mat4 &t_projectView) override;

 private:
  static constexpr unsigned int ConvexFloatCount = 17;
  static constexpr unsigned int ConvexVertexCount = 4;
  static constexpr unsigned int ConvexIndiceCount = 6;
  static constexpr unsigned int MaxBatchCount = 1000;
  static constexpr unsigned int MaxVertexCount = ConvexVertexCount * MaxBatchCount;
  static constexpr unsigned int MaxIndiceCount = ConvexIndiceCount * MaxBatchCount;

  std::vector<float> m_vertices;
  unsigned int m_VBO{}, m_VAO{}, m_EBO{};
  const Shader &m_shader;
  void ClearBatchBuffer();
  bool CanCommit() const;
};

#endif //MODERNOPENGL__CONVEXBATCH_H_
