#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader {
 public:
  Shader(const char *t_vertexPath, const char *t_fragmentPath);

  void Use() const;
  void SetBool(const std::string &t_name, bool t_value) const;
  void SetInt(const std::string &t_name, int t_value) const;
  void SetFloat(const std::string &t_name, float t_value) const;
  void SetVec2(const std::string &t_name, const glm::vec2 &t_value) const;
  void SetVec2(const std::string &t_name, float t_x, float t_y) const;
  void SetVec3(const std::string &t_name, const glm::vec3 &t_value) const;
  void SetVec3(const std::string &t_name, float t_x, float t_y, float t_z) const;
  void SetVec4(const std::string &t_name, const glm::vec4 &t_value) const;
  void SetVec4(const std::string &t_name, float t_x, float t_y, float t_z, float t_w) const;
  void SetMat2(const std::string &t_name, const glm::mat2 &t_mat) const;
  void SetMat3(const std::string &t_name, const glm::mat3 &t_mat) const;
  void SetMat4(const std::string &t_name, const glm::mat4 &t_mat) const;
  void SetIntArray(const std::string &t_name, const GLint *t_array) const;
  void SetUniformInt(const std::string &t_name, const GLuint t_value) const;

 private:
  unsigned int m_id;
  static void CheckCompileErrors(unsigned int t_shader, const std::string &t_type);
};
#endif