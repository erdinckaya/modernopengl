#include "ConvexBatch.h"
#include "../mesh/ConvexVertex.h"
// Create convex batch which will be using for drawing simple rectangle and circle.
ConvexBatch::ConvexBatch(const Shader &t_shader) : m_shader(t_shader) {
  // Create vertex array object
  glGenVertexArrays(1, &m_VAO);
  // Create vertex buffer object
  glGenBuffers(1, &m_VBO);
  // Create element buffer object for indices
  glGenBuffers(1, &m_EBO);

  glBindVertexArray(m_VAO);

  // Bind array buffer.
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  // A great thing about structs is that their memory layout is sequential for all its items.
  // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
  // again translates to 3/2 floats which translates to a byte array.
  glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(ConvexVertex), nullptr, GL_DYNAMIC_DRAW);

  // set attributes
  // Map convex vertex data struct into vertex data.
  GLuint index = 0;
  glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, sizeof(ConvexVertex), nullptr);
  glEnableVertexAttribArray(index++);

  glVertexAttribPointer(index,
                        3,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ConvexVertex),
                        (void *) offsetof(ConvexVertex, translation));
  glEnableVertexAttribArray(index++);

  glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(ConvexVertex), (void *) offsetof(ConvexVertex, scale));
  glEnableVertexAttribArray(index++);

  glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, sizeof(ConvexVertex), (void *) offsetof(ConvexVertex, rotation));
  glEnableVertexAttribArray(index++);

  glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, sizeof(ConvexVertex), (void *) offsetof(ConvexVertex, color));
  glEnableVertexAttribArray(index++);

  glVertexAttribPointer(index,
                        1,
                        GL_FLOAT,
                        GL_FALSE,
                        sizeof(ConvexVertex),
                        (void *) offsetof(ConvexVertex, borderThickness));
  glEnableVertexAttribArray(index++);

  glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, sizeof(ConvexVertex), (void *) offsetof(ConvexVertex, fill));
  glEnableVertexAttribArray(index);

  // Since this renders basic quad indices are same for all types.
  constexpr unsigned int quadIndices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  // Load up indices.
  unsigned int indices[MaxIndiceCount];
  unsigned int offset = 0;
  for (int i = 0; i < MaxIndiceCount; i += ConvexIndiceCount) {
    for (int j = 0; j < ConvexIndiceCount; ++j) {
      indices[i + j] = quadIndices[j] + offset;
    }
    offset += ConvexVertexCount;
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);
}

// Add convex render data if it reached to max limit of batch it has to commit first.
void ConvexBatch::Add(GLuint t_textureId, std::vector<float> &t_vertices, const glm::mat4 &t_pvm) {
  if (CanCommit()) {
    Draw(t_pvm);
  }
  m_vertices.insert(std::end(m_vertices), std::begin(t_vertices), std::end(t_vertices));
}
// Draw all batches.
void ConvexBatch::Draw(const glm::mat4 &t_projectView) {
  // If buffer is empty return nothing to do.
  if (m_vertices.empty()) {
    ClearBatchBuffer();
    return;
  }

  // Use shader
  m_shader.Use();
  // Assign the projection matrix.
  m_shader.SetMat4("pv", t_projectView);

  // Bind vertexes
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(float), &m_vertices[0]);

  // Draw
  const int kVertexCount = static_cast<int>(m_vertices.size());
  const unsigned int indiceCount = (kVertexCount * ConvexIndiceCount) / (ConvexVertexCount * ConvexFloatCount);
  glBindVertexArray(m_VAO);
  glDrawElements(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);

  // clear buffer.
  ClearBatchBuffer();
}
void ConvexBatch::ClearBatchBuffer() {
  m_vertices.clear();
}
bool ConvexBatch::CanCommit() const {
  return m_vertices.size() / ConvexFloatCount >= MaxVertexCount;
}
