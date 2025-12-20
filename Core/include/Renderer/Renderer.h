#pragma once
#include "utils.h"
#include "pch.h"
#include "RendererImplementation.h"
#include "Image.h"
#include "Shader.h"

namespace Core {
    class CORE_API Renderer {
    public:
        static void Init();
        static std::unique_ptr<Renderer>& GetRenderer();
        void Draw(Image& pic, int xCoord, int yCoord);
        void Draw(Image& pic, int xCoord, int yCoord, Shader& shaders);
        void ClearScreen();
        void ClearScreen(std::vector<float>& clearColor);
    private:
        Renderer();
        std::unique_ptr<RendererImplementation> mImplementation;
        inline static std::unique_ptr<Renderer> mInstance;
    };
}