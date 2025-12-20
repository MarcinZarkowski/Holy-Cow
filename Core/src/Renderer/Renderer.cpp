#include "Renderer/Renderer.h"
#include "Renderer/RendererImplementation.h"
#include "GLFWsrc/RendererGLFW.h"
#include "Renderer/Image.h"
#include "Renderer/Shader.h"
#include "glad/glad.h"

namespace Core {
    Renderer::Renderer() {
        #ifdef CORE_OPENGL
            mImplementation = std::unique_ptr<RendererImplementation>{ new RendererGLFW };
        #else
            #only_OpenGL_is_implemented_so_far
        #endif
    }

    void Renderer::Init() {
        if (mInstance == nullptr) {
            mInstance = std::unique_ptr<Renderer>{ new Renderer};
        }
    }

    std::unique_ptr<Renderer>& Renderer::GetRenderer() {
        return mInstance;
    }

    void Renderer::Draw(Image& pic, int xCoord, int yCoord) {
        mInstance->mImplementation->Draw(pic, xCoord, yCoord);
    }

    void Renderer::Draw(Image& pic, int xCoord, int yCoord, Shader& shader) {
        mInstance->mImplementation->Draw(pic, xCoord, yCoord, shader);
    }

    void Renderer::ClearScreen() {
        mInstance->mImplementation->ClearScreen();
    }

    void Renderer::ClearScreen(std::vector<float>& clearColor) {
        mInstance->mImplementation->ClearScreen(clearColor);
    }
}