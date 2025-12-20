#pragma once
#include "pch.h"
#include "utils.h"
#include "ShaderImplementation.h"

namespace Core {
    class CORE_API Shader {
    public:
        Shader(const std::string& vertexFile, const std::string& fragmentFile);
        void SetIntegerUniform(const std::string& uniformName, const std::vector<int>& values);
    private:
        std::unique_ptr<ShaderImplementation> mImplementation;
        void Bind();

        friend class RendererGLFW;
    };
}