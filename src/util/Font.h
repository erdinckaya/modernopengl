#pragma once
#include <unordered_map>
#include <GL/glew.h>
#include "Glyph.h"
#include "Types.h"

/// Simple font data struct.
struct Font {
  explicit Font(int t_size = 0, int t_type = 0, const char *t_filePath = nullptr)
      : size(t_size), type(t_type),
        filePath(t_filePath) {
  }

  Font(const Font &) = delete;
  void operator=(Font const &) = delete;

  ~Font() {
    for (auto &kv : glyphs) {
      glDeleteTextures(1, &kv.second.textureId);
    }
  }

  int size;
  int type;
  const char *filePath;
  std::unordered_map<char, Glyph> glyphs{};
};
