#ifndef MODERNOPENGL__GLYPH_H_
#define MODERNOPENGL__GLYPH_H_

#include <glm/glm.hpp>
struct Glyph {
  unsigned int textureId;   // ID handle of the glyph texture
  glm::ivec2 size;    // Size of glyph
  glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
  signed long advance;    // Horizontal offset to advance to next glyph
};

#endif //MODERNOPENGL__GLYPH_H_
