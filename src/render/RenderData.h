#ifndef MODERNOPENGL__RENDERDATA_H_
#define MODERNOPENGL__RENDERDATA_H_

#include <vector>
struct RenderData {

  RenderData(std::vector<float> vertices, int batch_type, unsigned int texture_id)
      : vertices(std::move(vertices)), batchType(batch_type), textureId(texture_id) {}

  std::vector<float> vertices;
  int batchType;
  unsigned int textureId;
};

#endif //MODERNOPENGL__RENDERDATA_H_
