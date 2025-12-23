#include "Renderer/Image.h"
#include "GLFWsrc/ImageGLFW.h"
#include "Renderer/ImageImplementation.h"

namespace Core {
Image::Image(const std::string &fileName, int targetSize) {
#ifdef CORE_OPENGL
  mImplementation =
      std::unique_ptr<ImageImplementation>{new ImageGLFW{fileName, targetSize}};
#else
#only_OpenGL_is_implemented_so_far
#endif
}

int Image::GetWidth() const { return mImplementation->GetWidth(); }

int Image::GetHeight() const { return mImplementation->GetHeight(); }

void Image::Bind() { mImplementation->Bind(); }
} // namespace Core