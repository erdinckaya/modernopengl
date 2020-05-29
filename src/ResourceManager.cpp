#include "ResourceManager.h"

const Glyph &ResourceManager::GetGlyph(const char *t_text, int t_fontType) const {
  if (m_fonts[t_fontType]->glyphs.find(*t_text) == m_fonts[t_fontType]->glyphs.end()) {
    return m_fonts[t_fontType]->glyphs['_'];
  }
  return m_fonts[t_fontType]->glyphs[*t_text];
}
const Texture &ResourceManager::GetTexture(int t_textureType) const {
  return *m_textures[t_textureType];
}

const Shader &ResourceManager::GetShader(int t_batchType) const {
  return *m_shaders[t_batchType];
}

