#include "GLFWsrc/ImageGLFW.h"
#include "glad/glad.h"
#include "stbi.h"
#include "utils.h"

namespace Core {
ImageGLFW::ImageGLFW(const std::string &fileName, int targetSize) {
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
    unsigned char *processedData = data;
    int finalWidth = mWidth;
    int finalHeight = mHeight;

    // Resize to square if targetSize is specified
    if (targetSize > 0) {
      int newSize = targetSize * targetSize * nrChannels;
      unsigned char *resizedData = new unsigned char[newSize];

      // Simple nearest-neighbor resize
      for (int y = 0; y < targetSize; y++) {
        for (int x = 0; x < targetSize; x++) {
          int srcX = (x * mWidth) / targetSize;
          int srcY = (y * mHeight) / targetSize;
          int srcIdx = (srcY * mWidth + srcX) * nrChannels;
          int dstIdx = (y * targetSize + x) * nrChannels;

          for (int c = 0; c < nrChannels; c++) {
            resizedData[dstIdx + c] = data[srcIdx + c];
          }
        }
      }

      stbi_image_free(data);
      processedData = resizedData;
      finalWidth = targetSize;
      finalHeight = targetSize;
    }

    mWidth = finalWidth;
    mHeight = finalHeight;

    GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format,
                 GL_UNSIGNED_BYTE, processedData);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (targetSize > 0) {
      delete[] processedData;
    } else {
      stbi_image_free(processedData);
    }
  } else {
    CORE_ERROR("Failed to load texture");
  }
}

int ImageGLFW::GetWidth() const { return mWidth; }

int ImageGLFW::GetHeight() const { return mHeight; }

ImageGLFW::~ImageGLFW() { glDeleteTextures(1, &mTextureID); }

void ImageGLFW::Bind() { glBindTexture(GL_TEXTURE_2D, mTextureID); }
} // namespace Core