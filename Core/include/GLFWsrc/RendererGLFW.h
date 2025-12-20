#pragma once
#include "GLFWsrc/ShaderGLFW.h"
#include "Renderer/Image.h"
#include "Renderer/RendererImplementation.h"
#include "Renderer/Shader.h"

namespace Core {
class RendererGLFW : public RendererImplementation {
public:
  RendererGLFW();

  void Draw(Image &pic, int xCoord, int yCoord) override;
  void Draw(Image &pic, int xCoord, int yCoord, Shader &shaders) override;

  void ClearScreen() override;
  void ClearScreen(std::vector<float>& clearColor) override;

  ~RendererGLFW();

private:
  ShaderGLFW mDefaultShaders{"../Assets/Shaders/defaultVertexShader.glsl",
                             "../Assets/Shaders/defaultFragmentShader.glsl"};
};
} // namespace Core
