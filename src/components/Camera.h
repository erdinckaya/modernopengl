#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <GL/glew.h>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum class CameraMovement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

// Default camera values
constexpr float CAMERA_DEFAULT_YAW = -90.0f;
constexpr float CAMERA_DEFAULT_PITCH = 0.0f;
constexpr float CAMERA_DEFAULT_SPEED = 2.5f;
constexpr float CAMERA_DEFAULT_SENSITIVITY = 0.1f;
constexpr float CAMERA_DEFAULT_ZOOM = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera {

 public:
  // Constructor with vectors
  explicit Camera(glm::vec3 t_position = glm::vec3(0.0f, 0.0f, 0.0f),
                  glm::vec3 t_up = glm::vec3(0.0f, 1.0f, 0.0f),
                  float t_yaw = CAMERA_DEFAULT_YAW,
                  float t_pitch = CAMERA_DEFAULT_PITCH);
  // Constructor with scalar values
  Camera(float t_posX, float t_posY, float t_posZ, float t_upX, float t_upY, float t_upZ, float t_yaw, float t_pitch);

  // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
  glm::mat4 ViewMatrix() const;

  // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
  void ProcessKeyboard(CameraMovement t_direction, float t_deltaTime);

  // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
  void ProcessMouseMovement(float t_xoffset, float t_yoffset, GLboolean t_constrainPitch = true);

  // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
  void ProcessMouseScroll(float t_yoffset);

  float Zoom() const;

 private:
  // Calculates the front vector from the Camera's (updated) Euler Angles
  void UpdateCameraVectors();
  // Camera Attributes
  glm::vec3 m_position;
  glm::vec3 m_front;
  glm::vec3 m_up{};
  glm::vec3 m_right{};
  glm::vec3 m_worldUp;
  // Euler Angles
  float m_yaw;
  float m_pitch;
  // Camera options
  float m_movementSpeed;
  float m_mouseSensitivity;
  float m_zoom;
};
#endif