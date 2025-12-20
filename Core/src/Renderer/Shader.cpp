#include "pch.h"
#include "Renderer/Shader.h"
#include "GLFWsrc/ShaderGLFW.h"

namespace Core {
    Shader::Shader(const std::string &vertexFile, const std::string &fragmentFile) {
        #ifdef CORE_OPENGL
            mImplementation = std::unique_ptr<ShaderImplementation>{ new ShaderGLFW{vertexFile, fragmentFile} };
        #else
            #only_OpenGL_is_implemented_so_far
        #endif
    }

    void Shader::SetIntegerUniform(const std::string &uniformName, const std::vector<int> &values) {
        mImplementation->SetIntegerUniform(uniformName, values);
    }

    void Shader::Bind() {
        mImplementation->Bind();
    }

}