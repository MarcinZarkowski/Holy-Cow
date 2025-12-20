#pragma once
#include "Renderer/Shader.h"
#include "Renderer/Image.h"

namespace Core {
    class Image;

    class RendererImplementation {
    public:

        virtual void Draw(Image& pic, int xCoord, int yCoord) = 0;
        virtual void Draw(Image& pic, int xCoord, int yCoord, Shader& shaders) = 0;
        virtual void ClearScreen() = 0;
        virtual void ClearScreen(std::vector<float>& clearColor) = 0;
        virtual ~RendererImplementation() = default;
    };
}