#include <SDL2/SDL_image.h>
#include <iostream>
#include "Texture.h"

Texture::Texture(const char *t_fileLoc) {
  m_textureID = 0;
  m_width = 0;
  m_height = 0;
  m_fileLocation = t_fileLoc;
  std::cout<<"Texture created "<<t_fileLoc<<std::endl;
  LoadTexture();
}

void Texture::LoadTexture() {
  // load and create a texture
  // -------------------------
  glGenTextures(1, &m_textureID);
  glBindTexture(GL_TEXTURE_2D,
                m_textureID); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D,
                  GL_TEXTURE_WRAP_S,
                  GL_REPEAT);    // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  auto surface = IMG_Load(m_fileLocation.c_str());
  if (surface) {
    m_width = surface->w;
    m_height = surface->h;
    GLenum mode = 0;
    switch (surface->format->BytesPerPixel)
    {
      case 4:
        mode = GL_RGBA;
        break;
      case 3:
        mode = GL_RGB;
        break;
      case 1:
        mode = GL_LUMINANCE_ALPHA;
        break;
      default:
        std::cerr<<"Image with unknown channel profile"<<std::endl;
        break;
    }
    GLenum format = mode;
#ifdef __APPLE__
    format = GL_BGRA;
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr<<"Failed to load texture "<<m_fileLocation<<std::endl;
  }
  SDL_FreeSurface(surface);
}

void Texture::Use() const {
  glBindTexture(GL_TEXTURE_2D, m_textureID);
}

void Texture::ClearTexture() {
  glDeleteTextures(1, &m_textureID);
  m_textureID = 0;
  m_width = 0;
  m_height = 0;
  m_fileLocation.clear();
}

Texture::~Texture() {
  ClearTexture();
}
GLuint Texture::TextureId() const {
  return m_textureID;
}
int Texture::Width() const {
  return m_width;
}
int Texture::Height() const {
  return m_height;
}
const std::string &Texture::FileLocation() const {
  return m_fileLocation;
}
glm::vec2 Texture::Size() const {
  return glm::vec2(m_width, m_height);
}
