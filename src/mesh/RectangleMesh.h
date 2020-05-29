#ifndef MODERNOPENGL__RECTANGLEMESH_H_
#define MODERNOPENGL__RECTANGLEMESH_H_
#include "ConvexMesh.h"
struct RectangleMesh : public ConvexMesh<RectangleMesh> {
  glm::vec2 Size() const {
    return m_scale;
  }
};

#endif //MODERNOPENGL__RECTANGLEMESH_H_
