#pragma once

#include <GL/glew.h>

#include <string>
#include <glm/vec2.hpp>

struct Texture {
 public:
  explicit Texture(const char *t_fileLoc);

  // Since it bounded with opengl texture lifetime.
  // This struct is basically singleton.
  Texture(const Texture &) = delete;
  void operator=(Texture const &) = delete;

  void Use() const;
  ~Texture();

  GLuint TextureId() const;
  int Width() const;
  int Height() const;
  glm::vec2 Size() const;
  const std::string &FileLocation() const;

 private:
  void LoadTexture();
  void ClearTexture();

  GLuint m_textureID;
  int m_width, m_height;
  std::string m_fileLocation;
};

