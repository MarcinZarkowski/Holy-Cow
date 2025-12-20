#include "GLFWsrc/ShaderGLFW.h"
#include "Renderer/Shader.h"
#include "glad/glad.h"
#include "utils.h"

namespace Core {
ShaderGLFW::ShaderGLFW(const std::string &vertexFile,
                       const std::string &fragmentFile) {
  std::string vertexCode = ReadFile(vertexFile);
  const char *vertexShaderSource = vertexCode.c_str();

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    CORE_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog);
  }

  std::string fragmentCode = ReadFile(fragmentFile);
  const char *fragmentShaderSource = fragmentCode.c_str();

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    CORE_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog);
  }

  mShaderProgram = glCreateProgram();
  glAttachShader(mShaderProgram, vertexShader);
  glAttachShader(mShaderProgram, fragmentShader);
  glLinkProgram(mShaderProgram);

  glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
    CORE_ERROR("ERROR::SHADER PROGRAM LINKING FAILED\n" << infoLog);
  }
  glUseProgram(mShaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

std::string ShaderGLFW::ReadFile(const std::string &fileName) {
  std::ifstream input{fileName};

  if (!input.is_open())
    CORE_ERROR("Failed to open" << fileName);

  std::string res;
  std::string line;
  while (std::getline(input, line)) {
    res += line + "\n";
  }

  input.close();

  return res;
}

void ShaderGLFW::Bind() { glUseProgram(mShaderProgram); }

void ShaderGLFW::SetIntegerUniform(const std::string &uniformName,
                                   const std::vector<int> &values) {
  glUseProgram(mShaderProgram);
  int location{glGetUniformLocation(mShaderProgram, uniformName.c_str())};

  switch (values.size()) {
  case 1:
    glUniform1i(location, values[0]);
    break;
  case 2:
    glUniform2i(location, values[0], values[1]);
    break;
  case 3:
    glUniform3i(location, values[0], values[1], values[2]);
    break;
  case 4:
    glUniform4i(location, values[0], values[1], values[2], values[3]);
    break;
  default:
    CORE_ERROR("Invalid uniform size");
  }
}

ShaderGLFW::~ShaderGLFW() { glDeleteProgram(mShaderProgram); }
} // namespace Core
