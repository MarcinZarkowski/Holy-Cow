#pragma once
#include "Renderer/ImageImplementation.h"
#include "pch.h"


namespace Core {
    class ImageGLFW : public ImageImplementation {
    public:
        ImageGLFW(const std::string& fileName);

        int GetWidth() const override;
        int GetHeight () const override;

        ~ImageGLFW() override;

    private:
        unsigned int mTextureID{ 0 };
        int mWidth{ 0 };
        int mHeight{ 0 };

        void Bind() override;
    };
}
