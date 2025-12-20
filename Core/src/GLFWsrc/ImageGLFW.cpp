#include "GLFWsrc/ImageGLFW.h"
#include "glad/glad.h"
#include "stbi.h"
#include "utils.h"

namespace Core {
ImageGLFW::ImageGLFW(const std::string &fileName) {
  glGenTextures(1, &mTextureID);
  glBindTexture(GL_TEXTURE_2D, mTextureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  int nrChannels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char *data =
      stbi_load(fileName.c_str(), &mWidth, &mHeight, &nrChannels, 0);
  if (data) {
    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    CORE_ERROR("Failed to load texture");
  }
  stbi_image_free(data);
}

int ImageGLFW::GetWidth() const { return mWidth; }

int ImageGLFW::GetHeight() const { return mHeight; }

ImageGLFW::~ImageGLFW() { glDeleteTextures(1, &mTextureID); }

void ImageGLFW::Bind() { glBindTexture(GL_TEXTURE_2D, mTextureID); }
} // namespace Core