#pragma once
#include "ImageImplementation.h"
#include "pch.h"
#include "utils.h"

namespace Core {
class RendererGLFW; // Forward declaration to avoid circular include

class CORE_API Image {
public:
  Image(const std::string &fileName, int targetSize = -1);

  int GetWidth() const;
  int GetHeight() const;

private:
  std::unique_ptr<ImageImplementation> mImplementation;

  void Bind();
  friend class RendererGLFW;
};
} // namespace Core
