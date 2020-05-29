#ifndef MODERNOPENGL__TEXTMESH_H_
#define MODERNOPENGL__TEXTMESH_H_
#include <vector>
#include <string>
#include "TextureMesh.h"

struct TextMesh {
 public:
  TextMesh();

  const std::vector<TextureMesh>& CharMeshes() const;

  const std::string &Text() const;
  TextMesh& SetText(std::string t_text);
  const glm::mat4 &Model() const;
  TextMesh& SetModel(const glm::mat4 &t_model);
  const glm::vec4 &Color() const;
  TextMesh& SetColor(const glm::vec4 &t_color);
  float SortingOrder() const;
  TextMesh& SetSortingOrder(float t_sortingOrder);
  TextMesh& Build();

  const glm::vec2& Size() const;
 private:

  static constexpr float DefaultTextScale = 0.3f;

  std::string m_text;
  std::vector<TextureMesh> m_chars;
  glm::mat4 m_model;
  glm::vec4 m_color;
  glm::vec2 m_size;
  float m_sortingOrder;
};

#endif //MODERNOPENGL__TEXTMESH_H_
