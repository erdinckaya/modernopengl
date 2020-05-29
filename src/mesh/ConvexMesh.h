#ifndef MODERNOPENGL__CONVEXMESH_H_
#define MODERNOPENGL__CONVEXMESH_H_

#include "../util/Rect.h"
#include <vector>
#include <glm/glm.hpp>

template<typename T>
struct ConvexMesh {
 public:
  const std::vector<float> &Vertices() const {
    return m_vertices;
  }
  const glm::vec3 &Translation() const {
    return m_translation;
  }
  T &SetTranslation(const glm::vec3 &t_translation) {
    m_translation = t_translation;
    return *static_cast<T *>(this);
  }

  const glm::vec3 &Scale() const {
    return m_scale;
  }
  T &SetScale(const glm::vec3 &t_scale) {
    m_scale = t_scale;
    return *static_cast<T *>(this);
  }

  const glm::vec3 &Rotation() const {
    return m_rotation;
  }
  T &SetRotation(const glm::vec3 &t_rotation) {
    m_rotation = t_rotation;
    return *static_cast<T *>(this);
  }

  const glm::vec4 &Color() const {
    return m_color;
  }
  T &SetColor(const glm::vec4 &t_color) {
    m_color = t_color;
    return *static_cast<T *>(this);
  }

  float BorderThickness() const {
    return m_borderThickness;
  }
  T &SetBorderThickness(float t_borderThickness) {
    m_borderThickness = t_borderThickness;
    return *static_cast<T *>(this);
  }

  float Fill() const {
    return m_fill;
  }
  T &FetFill(float t_fill) {
    m_fill = t_fill;
    return *static_cast<T *>(this);
  }

  float SortingOrder() const {
    return m_sortingOrder;
  }
  T &SetSortingOrder(float t_sortingOrder) {
    m_sortingOrder = t_sortingOrder;
    return *static_cast<T *>(this);
  }

  T &Build() {
    const float w = 0.5f;
    const float h = 0.5f;
    const float zCoefficient = 0.0001f;
    const float z = m_sortingOrder * zCoefficient;

    m_vertices = {
        // top right
        w, h,
        m_translation.x, m_translation.y, z,
        m_scale.x, m_scale.y, m_scale.z,
        m_rotation.x, m_rotation.y, m_rotation.z,
        m_color.x, m_color.y, m_color.z, m_color.w,
        m_borderThickness,
        m_fill,

        // bottom right
        w, -h,
        m_translation.x, m_translation.y, z,
        m_scale.x, m_scale.y, m_scale.z,
        m_rotation.x, m_rotation.y, m_rotation.z,
        m_color.x, m_color.y, m_color.z, m_color.w,
        m_borderThickness,
        m_fill,

        // bottom left
        -w, -h,
        m_translation.x, m_translation.y, z,
        m_scale.x, m_scale.y, m_scale.z,
        m_rotation.x, m_rotation.y, m_rotation.z,
        m_color.x, m_color.y, m_color.z, m_color.w,
        m_borderThickness,
        m_fill,

        // top left
        -w, h,
        m_translation.x, m_translation.y, z,
        m_scale.x, m_scale.y, m_scale.z,
        m_rotation.x, m_rotation.y, m_rotation.z,
        m_color.x, m_color.y, m_color.z, m_color.w,
        m_borderThickness,
        m_fill
    };

    return *static_cast<T *>(this);
  }

 protected:
  std::vector<float> m_vertices;
  glm::vec3 m_translation{0.f};
  glm::vec3 m_scale{1.0f};
  glm::vec3 m_rotation{0.0f};
  glm::vec4 m_color{1.0f};
  float m_borderThickness{0.0f}; // 0 - 1.0f
  float m_fill{1.0f};
  float m_sortingOrder{0};
};

#endif //MODERNOPENGL__CONVEXMESH_H_
