#include "TextureMesh.h"

TextureMesh::TextureMesh(const glm::vec2 &t_size, const float &t_sortingOrder) :
    m_clip(0.0f, 0.0f, 1.0f, 1.0f),
    m_sortingOrder(t_sortingOrder),
    m_model(1.0f),
    m_color(1.0f),
    m_textureId(0) {
  SetSize(t_size);
}
void TextureMesh::SetupVertices() {
  const float w = m_size.x * 0.5f;
  const float h = m_size.y * 0.5f;
  const float zCoefficient = 0.0001f;
  const float z = m_sortingOrder * zCoefficient;
  const float textureIndex = 0.0f;

  glm::vec4 vec1(w, h, 0, 1);
  vec1 = m_model * vec1;
  glm::vec4 vec2(w, -h, 0, 1);
  vec2 = m_model * vec2;
  glm::vec4 vec3(-w, -h, 0, 1);
  vec3 = m_model * vec3;
  glm::vec4 vec4(-w, h, 0, 1);
  vec4 = m_model * vec4;

  m_vertices = {
      // positions // texture coords
      vec1.x, vec1.y, z,                    // top right
      m_clip.x + m_clip.w, m_clip.y + m_clip.h,
      m_color.x, m_color.y, m_color.z, m_color.w,
      textureIndex,
      vec2.x, vec2.y, z,                    // bottom right
      m_clip.x + m_clip.w, m_clip.y,
      m_color.x, m_color.y, m_color.z, m_color.w,
      textureIndex,
      vec3.x, vec3.y, z,                    // bottom left
      m_clip.x, m_clip.y,
      m_color.x, m_color.y, m_color.z, m_color.w,
      textureIndex,
      vec4.x, vec4.y, z,                    // top left
      m_clip.x, m_clip.y + m_clip.h,
      m_color.x, m_color.y, m_color.z, m_color.w,
      textureIndex,
  };
}

void TextureMesh::SetClip(const Rectf &t_clip) {
  m_clip = t_clip;
  RefreshMesh();
}
void TextureMesh::RefreshMesh() {
  this->SetupVertices();
}
float TextureMesh::SortingOrder() const {
  return m_sortingOrder;
}
void TextureMesh::SetSortingOrder(float t_sortingOrder) {
  m_sortingOrder = t_sortingOrder;
  RefreshMesh();
}
glm::vec2 TextureMesh::Size() const {
  return m_size;
}
void TextureMesh::SetSize(const glm::vec2 &t_size) {
  if (t_size.x == 0 || t_size.y == 0) {
    m_size = t_size;
  } else {
    if (t_size.x > t_size.y) {
      m_size.x = 1.0f;
      m_size.y = t_size.y / t_size.x;
    } else {
      m_size.y = 1.0f;
      m_size.x = t_size.x / t_size.y;
    }
  }

  RefreshMesh();
}

const std::vector<float> &TextureMesh::Vertices() const {
  return m_vertices;
}

const Rectf &TextureMesh::Clip() const {
  return m_clip;
}
void TextureMesh::SetModel(const glm::mat4 &t_model) {
  m_model = t_model;
  RefreshMesh();
}
const glm::mat4 &TextureMesh::Model() const {
  return m_model;
}
glm::vec4 TextureMesh::Color() const {
  return m_color;
}
void TextureMesh::SetColor(const glm::vec4 &t_color) {
  m_color = t_color;
  RefreshMesh();
}
void TextureMesh::ForceSize(const glm::vec2 &t_size) {
  m_size = t_size;
  RefreshMesh();
}
void TextureMesh::SetTextureId(unsigned int t_textureId) {
  m_textureId = t_textureId;
}
const unsigned int &TextureMesh::TextureId() const {
  return m_textureId;
}
