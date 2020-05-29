#ifndef MODERNOPENGL__RESOURCEMANAGER_H_
#define MODERNOPENGL__RESOURCEMANAGER_H_

#include <array>
#include <memory>
#include "util/Font.h"
#include "util/Types.h"
#include "components/Texture.h"
#include "components/Shader.h"
#include <vector>
#include <freetype/tttags.h>

constexpr int TEST_FONT_SIZE = 50;
// Singleton class.
class ResourceManager {
 public:
  static ResourceManager &instance() {
    static ResourceManager instance;
    return instance;
  }

 private:
  ResourceManager() = default;

 public:
  ResourceManager(ResourceManager const &) = delete;
  void operator=(ResourceManager const &) = delete;

  template<unsigned long TextureCount, unsigned long ShaderCount, unsigned long FontCount>
  void LoadResources(const std::array<const char *, TextureCount> &t_textures,
                     const std::array<const char *, ShaderCount> &t_shaders,
                     const std::array<const char *, FontCount> &t_fonts) {
    static_assert(ShaderType::_size() * 2 == ShaderCount, "Total shaders must be twice of shader types. See `ShaderType` in Types.h");
    LoadTextures(t_textures);
    LoadShaders(t_shaders);
    LoadFonts(t_fonts);
  }

  const Glyph &GetGlyph(const char *t_text, int t_fontType) const;
  const Texture &GetTexture(int t_textureType) const;
  const Shader &GetShader(int t_batchType) const;

 private:

  template<unsigned long TextureCount>
  void LoadTextures(const std::array<const char *, TextureCount> &t_textures) {
    for (auto t_texture : t_textures) {
      m_textures.emplace_back(std::make_unique<Texture>(t_texture));
    }
  }
  template<unsigned long ShaderCount>
  void LoadShaders(const std::array<const char *, ShaderCount> &t_shaders) {
    for (int i = 0; i < t_shaders.size(); i += 2) {
      auto vert = t_shaders[i];
      auto frag = t_shaders[i + 1];
      m_shaders.emplace_back(std::make_unique<Shader>(vert, frag));
    }
  }
  template<unsigned long FontCount>
  void LoadFonts(const std::array<const char *, FontCount> &t_fonts) {
    // Prepare fonts
    for (int i = 0; i < t_fonts.size(); ++i) {
      m_fonts.emplace_back(std::make_unique<Font>(TEST_FONT_SIZE, i, t_fonts[i]));
    }

    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft)) {
      std::cerr<<"ERROR::FREETYPE: Could not init FreeType Library"<<std::endl;
    }

    for (auto &font : m_fonts) {
      FT_Face face{};

      // Load font as face
      if (FT_New_Face(ft, font->filePath, 0, &face)) {
        std::cerr<<"ERROR::FREETYPE: Failed to load font"<<std::endl;
      }

      // Set size to load glyphs as
      FT_Set_Pixel_Sizes(face, 0, font->size);

      // Disable byte-alignment restriction
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
          std::cerr<<"ERROR::FREETYTPE: Failed to load Glyph"<<std::endl;
          continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        font->glyphs[c].textureId = texture;
        font->glyphs[c].size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        font->glyphs[c].bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
        font->glyphs[c].advance = face->glyph->advance.x;

      }

      glBindTexture(GL_TEXTURE_2D, 0);
      FT_Done_Face(face);
    }
    FT_Done_FreeType(ft);
  }

  std::vector<std::unique_ptr<Font>> m_fonts;
  std::vector<std::unique_ptr<Texture>> m_textures;
  std::vector<std::unique_ptr<Shader>> m_shaders;
};

#endif //MODERNOPENGL__RESOURCEMANAGER_H_
