#include "Shader.h"

Shader::Shader(const char *t_vertexPath, const char *t_fragmentPath) {
  // 1. retrieve the vertex/fragment source code from filePath
  std::string vertexCode;
  std::string fragmentCode;
  std::ifstream vShaderFile;
  std::ifstream fShaderFile;
  // ensure ifstream objects can throw exceptions:
  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    // open files
    vShaderFile.open(t_vertexPath);
    fShaderFile.open(t_fragmentPath);
    std::stringstream vShaderStream, fShaderStream;
    // read file's buffer contents into streams
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();
    // close file handlers
    vShaderFile.close();
    fShaderFile.close();
    // convert stream into string
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  }
  catch (std::ifstream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
  }
  const char *vShaderCode = vertexCode.c_str();
  const char *fShaderCode = fragmentCode.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, nullptr);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, nullptr);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");
  // shader Program
  m_id = glCreateProgram();
  glAttachShader(m_id, vertex);
  glAttachShader(m_id, fragment);
  glLinkProgram(m_id);
  CheckCompileErrors(m_id, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer necessary
  glDeleteShader(vertex);
  glDeleteShader(fragment);
}
void Shader::Use() const {
  glUseProgram(m_id);
}
void Shader::SetBool(const std::string &t_name, bool t_value) const {
  glUniform1i(glGetUniformLocation(m_id, t_name.c_str()), (int) t_value);
}
void Shader::SetInt(const std::string &t_name, int t_value) const {
  glUniform1i(glGetUniformLocation(m_id, t_name.c_str()), t_value);
}
void Shader::SetFloat(const std::string &t_name, float t_value) const {
  glUniform1f(glGetUniformLocation(m_id, t_name.c_str()), t_value);
}
void Shader::SetVec2(const std::string &t_name, const glm::vec2 &t_value) const {
  glUniform2fv(glGetUniformLocation(m_id, t_name.c_str()), 1, &t_value[0]);
}
void Shader::SetVec2(const std::string &t_name, float t_x, float t_y) const {
  glUniform2f(glGetUniformLocation(m_id, t_name.c_str()), t_x, t_y);
}
void Shader::SetVec3(const std::string &t_name, const glm::vec3 &t_value) const {
  glUniform3fv(glGetUniformLocation(m_id, t_name.c_str()), 1, &t_value[0]);
}
void Shader::SetVec3(const std::string &t_name, float t_x, float t_y, float t_z) const {
  glUniform3f(glGetUniformLocation(m_id, t_name.c_str()), t_x, t_y, t_z);
}
void Shader::SetVec4(const std::string &t_name, const glm::vec4 &t_value) const {
  glUniform4fv(glGetUniformLocation(m_id, t_name.c_str()), 1, &t_value[0]);
}
void Shader::SetVec4(const std::string &t_name, float t_x, float t_y, float t_z, float t_w) const {
  glUniform4f(glGetUniformLocation(m_id, t_name.c_str()), t_x, t_y, t_z, t_w);
}
void Shader::SetMat2(const std::string &t_name, const glm::mat2 &t_mat) const {
  glUniformMatrix2fv(glGetUniformLocation(m_id, t_name.c_str()), 1, GL_FALSE, &t_mat[0][0]);
}
void Shader::SetMat3(const std::string &t_name, const glm::mat3 &t_mat) const {
  glUniformMatrix3fv(glGetUniformLocation(m_id, t_name.c_str()), 1, GL_FALSE, &t_mat[0][0]);
}
void Shader::SetMat4(const std::string &t_name, const glm::mat4 &t_mat) const {
  glUniformMatrix4fv(glGetUniformLocation(m_id, t_name.c_str()), 1, GL_FALSE, &t_mat[0][0]);
}
void Shader::SetIntArray(const std::string &t_name, const GLint *t_array) const {
  const unsigned int size = (int)sizeof(t_array) / sizeof(GLuint);
  glUniform1iv(glGetUniformLocation(m_id, t_name.c_str()), size, t_array);
}
void Shader::SetUniformInt(const std::string &t_name, const GLuint t_value) const {
  glUniform1i(glGetUniformLocation(m_id, t_name.c_str()), t_value);
}
void Shader::CheckCompileErrors(unsigned int t_shader, const std::string &t_type) {
  int success;
  char infoLog[1024];
  if (t_type != "PROGRAM") {
    glGetShaderiv(t_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(t_shader, 1024, nullptr, infoLog);
      std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << t_type << "\n" << infoLog
                << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  } else {
    glGetProgramiv(t_shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(t_shader, 1024, nullptr, infoLog);
      std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << t_type << "\n" << infoLog
                << "\n -- --------------------------------------------------- -- " << std::endl;
    }
  }
}


