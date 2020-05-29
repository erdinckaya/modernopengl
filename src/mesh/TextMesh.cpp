#include <glm/ext/matrix_transform.hpp>
#include "TextMesh.h"
#include "../util/Glyph.h"
#include "../ResourceManager.h"

TextMesh::TextMesh()
    : m_color(1.0f),
      m_model(1.0f),
      m_sortingOrder(1000.0f),
      m_text("EMPTY_TEXT"),
      m_size(0.0f) {

}

const std::vector<TextureMesh> &TextMesh::CharMeshes() const {
  return m_chars;
}
const std::string &TextMesh::Text() const {
  return m_text;
}
TextMesh &TextMesh::SetText(std::string t_text) {
  m_text = std::move(t_text);
  return *this;
}
const glm::mat4 &TextMesh::Model() const {
  return m_model;
}
TextMesh &TextMesh::SetModel(const glm::mat4 &t_model) {
  m_model = t_model;
  return *this;
}
const glm::vec4 &TextMesh::Color() const {
  return m_color;
}
TextMesh &TextMesh::SetColor(const glm::vec4 &t_color) {
  m_color = t_color;
  return *this;
}
TextMesh &TextMesh::Build() {
  m_chars.clear();
  auto startPos = glm::vec3(0.0f);
  int index = 0;

  for (char &c : m_text) {
    TextureMesh mesh(glm::vec2(1.0f, 1.0f), m_sortingOrder);
    const Glyph &glyph = ResourceManager::instance().GetGlyph(&c, 0);
    const float factor = DefaultTextScale / TEST_FONT_SIZE;
    const glm::vec2 textSize = glm::vec2(glyph.size.x * factor, glyph.size.y * factor);
    mesh.SetTextureId(glyph.textureId);
    mesh.SetSortingOrder(m_sortingOrder);
    mesh.SetColor(m_color);
    mesh.ForceSize(textSize);

    const float advance = glyph.advance >> 6;

    float x = glyph.bearing.x * factor;
    float y = (float) (glyph.bearing.y - glyph.size.y) * factor;
    y -= (DefaultTextScale - textSize.y) * 0.5f;
    x += textSize.x * 0.5f;
    auto textPos = startPos + glm::vec3(x, y, 0);
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, textPos);
    model = m_model * model;
    mesh.SetModel(model);
    m_chars.emplace_back(mesh);
    startPos.x += advance * factor;

    index++;
  }
  m_size.x = startPos.x;
  m_size.y = DefaultTextScale;

  return *this;
}
float TextMesh::SortingOrder() const {
  return m_sortingOrder;
}
TextMesh &TextMesh::SetSortingOrder(float t_sortingOrder) {
  m_sortingOrder = t_sortingOrder;
  return *this;
}

const glm::vec2 &TextMesh::Size() const {
  return m_size;
}


