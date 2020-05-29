#include "TextureBatch.h"
#include "../mesh/TextureMesh.h"
#include <glm/gtx/string_cast.hpp>

// Create texture batch which will be using for drawing images and textes.
TextureBatch::TextureBatch(const Shader &t_shader) : m_shader(t_shader) {
  // Create vertex array object
  glGenVertexArrays(1, &m_VAO);
  // Create vertex buffer object
  glGenBuffers(1, &m_VBO);
  // Create element buffer object for indices
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  // A great thing about structs is that their memory layout is sequential for all its items.
  // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
  // again translates to 3/2 floats which translates to a byte array.

  // Map texture vertex data into vertex buffer.
  glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(TextureVertex), nullptr, GL_DYNAMIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), nullptr);
  glEnableVertexAttribArray(0);
  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void *) offsetof(TextureVertex, texCoords));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void *) offsetof(TextureVertex, color));
  glEnableVertexAttribArray(2);

  glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(TextureVertex), (void *) offsetof(TextureVertex, index));
  glEnableVertexAttribArray(3);

  constexpr unsigned int quadIndices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  // Load up all indexes.
  unsigned int indices[MaxIndiceCount];
  unsigned int offset = 0;
  for (int i = 0; i < MaxIndiceCount; i += TextureIndiceCount) {
    for (int j = 0; j < TextureIndiceCount; ++j) {
      indices[i + j] = quadIndices[j] + offset;
    }
    offset += TextureVertexCount;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);

  // In order to use batch rendering we have to define texture indexes.
  // MaxTextureIndex can change by graphics cards. In my computer it is 16
  // So that I can render only 16 different textures in one draw call.
  m_shader.Use();
  const GLint sample_size = MaxTextureIndex;
  for (int i = 0; i < sample_size; ++i) {
    m_shader.SetUniformInt("textures[" + std::to_string(i) + "]", i);
  }
}

void TextureBatch::Add(GLuint t_textureId, std::vector<float> &t_vertices, const glm::mat4 &t_pvm) {
  // Calculate texture index;
  int textureIndex;
  if (!m_textures.count(t_textureId)) {
    int textId = static_cast<int>(m_textures.size());
    m_textures[t_textureId] = textId;
  }
  textureIndex = m_textures[t_textureId];
  // add vertices.
  UpdateTextureIndexes(t_vertices, textureIndex);
  m_vertices.insert(std::end(m_vertices), std::begin(t_vertices), std::end(t_vertices));
  if (CanCommit()) {
    Draw(t_pvm);
  }
}
void TextureBatch::Draw(const glm::mat4 &t_projectView) {
  if (m_vertices.empty()) {
    ClearBatchBuffer();
    return;
  }

  m_shader.Use();
  m_shader.SetMat4("pvm", t_projectView);

  // Bind textures indexes
  for (const auto &kv : m_textures) {
    glActiveTexture(GL_TEXTURE0 + kv.second);
    glBindTexture(GL_TEXTURE_2D, kv.first);
  }

  // Bind vertexes
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), m_vertices.data());

  // Draw
  const auto kVertexCount = static_cast<int>(m_vertices.size());
  const unsigned int indiceCount = (kVertexCount * TextureIndiceCount) / (TextureVertexCount * VertexFloatCount);
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);

  ClearBatchBuffer();
}
void TextureBatch::ClearBatchBuffer() {
  m_vertices.clear();
  m_textures.clear();
}
void TextureBatch::UpdateTextureIndexes(std::vector<float> &t_vertices, GLuint t_textureIndex) {
  const size_t size = t_vertices.size();
  for (size_t i = 0; i < size; i += VertexFloatCount) {
    t_vertices[i + VertexFloatCount - 1] = static_cast<float>(t_textureIndex);
  }
}
bool TextureBatch::CanCommit() const {
  return m_textures.size() >= MaxTextureIndex || m_vertices.size() / VertexFloatCount >= MaxVertexCount;
}

