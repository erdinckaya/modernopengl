#ifndef MODERNOPENGL__CIRCLEMESH_H_
#define MODERNOPENGL__CIRCLEMESH_H_
#include "ConvexMesh.h"

struct CircleMesh : public ConvexMesh<CircleMesh> {
  float Radius() const {
    return m_scale.x;
  }
};

#endif //MODERNOPENGL__CIRCLEMESH_H_
