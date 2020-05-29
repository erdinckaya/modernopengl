#include "Camera.h"
#include <iostream>
Camera::Camera(float t_posX,
               float t_posY,
               float t_posZ,
               float t_upX,
               float t_upY,
               float t_upZ,
               float t_yaw,
               float t_pitch)
    : Camera(glm::vec3(t_posX, t_posY, t_posZ), glm::vec3(t_upX, t_upY, t_upZ), t_yaw, t_pitch) {}

Camera::Camera(glm::vec3 t_position, glm::vec3 t_up, float t_yaw, float t_pitch) :
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
    m_movementSpeed(CAMERA_DEFAULT_SPEED),
    m_mouseSensitivity(CAMERA_DEFAULT_SENSITIVITY),
    m_zoom(CAMERA_DEFAULT_ZOOM),
    m_position(t_position),
    m_worldUp(t_up),
    m_yaw(t_yaw),
    m_pitch(t_pitch) {
  UpdateCameraVectors();
}
glm::mat4 Camera::ViewMatrix() const {
  return glm::lookAt(m_position, m_position + m_front, m_up);
}
void Camera::ProcessKeyboard(CameraMovement t_direction, float t_deltaTime) {
  float velocity = m_movementSpeed * t_deltaTime * 10;
  switch (t_direction) {
    case CameraMovement::FORWARD :m_position += m_front * velocity;
      break;
    case CameraMovement::BACKWARD:m_position -= m_front * velocity;
      break;
    case CameraMovement::LEFT:m_position -= m_right * velocity;
      break;
    case CameraMovement::RIGHT:m_position += m_right * velocity;
      break;
    default:break;
  }
  std::cout << "Camera pos " << m_position.x << " " << m_position.y << " " << m_position.z << std::endl;
}
void Camera::ProcessMouseMovement(float t_xoffset, float t_yoffset, GLboolean t_constrainPitch) {
  t_xoffset *= m_mouseSensitivity;
  t_yoffset *= m_mouseSensitivity;

  m_yaw += t_xoffset;
  m_pitch += t_yoffset;

  // Make sure that when pitch is out of bounds, screen doesn't get flipped
  if (t_constrainPitch) {
    if (m_pitch > 89.0f)
      m_pitch = 89.0f;
    if (m_pitch < -89.0f)
      m_pitch = -89.0f;
  }

  // Update Front, Right and Up Vectors using the updated Euler angles
  UpdateCameraVectors();
}
void Camera::ProcessMouseScroll(float t_yoffset) {
  if (m_zoom >= 1.0f && m_zoom <= 45.0f)
    m_zoom -= t_yoffset;
  if (m_zoom <= 1.0f)
    m_zoom = 1.0f;
  if (m_zoom >= 45.0f)
    m_zoom = 45.0f;
}
void Camera::UpdateCameraVectors() {
// Calculate the new Front vector
  glm::vec3 front;
  front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front.y = sin(glm::radians(m_pitch));
  front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  front = glm::normalize(front);
  // Also re-calculate the Right and Up vector
  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
  m_right = glm::normalize(glm::cross(front,m_worldUp));
  m_up = glm::normalize(glm::cross(m_right, front));
}
float Camera::Zoom() const {
  return m_zoom;
}
