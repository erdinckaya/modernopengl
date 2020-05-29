#ifndef MODERNOPENGL__TEXTUREBATCH_H_
#define MODERNOPENGL__TEXTUREBATCH_H_

#include <vector>
#include <unordered_map>
#include "../mesh/TextureVertex.h"
#include "../components/Texture.h"
#include "../components/Shader.h"
#include "BatchInterface.h"
#include "../components/Window.h"
#include <GL/glew.h>

class TextureBatch : public BatchInterface {
 public:
  explicit TextureBatch(const Shader &t_shader);

  void Add(GLuint t_textureId, std::vector<float> &t_vertices, const glm::mat4 &t_pvm) override;
  void Draw(const glm::mat4 &t_projectView) override;

 private:
  static constexpr unsigned int VertexFloatCount = 10;
  static constexpr unsigned int TextureVertexCount = 4;
  static constexpr unsigned int TextureIndiceCount = 6;
  static constexpr unsigned int MaxBatchCount = 1000;
  static constexpr unsigned int MaxVertexCount = TextureVertexCount * MaxBatchCount;
  static constexpr unsigned int MaxIndiceCount = TextureIndiceCount * MaxBatchCount;
  static constexpr unsigned int MaxTextureIndex = 16;

  std::unordered_map<GLuint, unsigned int> m_textures{};
  std::vector<float> m_vertices;
  unsigned int m_VBO{}, m_VAO{}, m_EBO{};
  const Shader &m_shader;
  void ClearBatchBuffer();
  static void UpdateTextureIndexes(std::vector<float> &t_vertices, GLuint t_textureIndex);
  bool CanCommit() const;
};

#endif //MODERNOPENGL__TEXTUREBATCH_H_
