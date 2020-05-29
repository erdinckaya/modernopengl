#ifndef MODERNOPENGL__TEXTUREMESH_H_
#define MODERNOPENGL__TEXTUREMESH_H_

#include "../util/Rect.h"
#include <vector>
#include <glm/glm.hpp>

struct TextureMesh {
 public:
  explicit TextureMesh(const glm::vec2 &t_size = glm::vec2(1.0f, 1.0f), const float &t_sortingOrder = 0.0f);
  float SortingOrder() const;
  void SetSortingOrder(float t_sortingOrder);
  glm::vec2 Size() const;
  void SetSize(const glm::vec2 &t_size);
  glm::vec4 Color() const;
  void SetColor(const glm::vec4 &t_color);

  const std::vector<float> &Vertices() const;

  void SetModel(const glm::mat4 &t_model);
  const glm::mat4 &Model() const;
  void SetClip(const Rectf &t_clip);
  const Rectf &Clip() const;

  void ForceSize(const glm::vec2& t_size);

  void SetTextureId(unsigned int t_textureId);
  const unsigned int &TextureId() const;

 private:
  void RefreshMesh();
  void SetupVertices();

  std::vector<float> m_vertices;
  Rectf m_clip;
  glm::vec2 m_size{};
  float m_sortingOrder;

  glm::mat4 m_model;
  glm::vec4 m_color;
  unsigned int m_textureId;
};

#endif //MODERNOPENGL__TEXTUREMESH_H_
