#pragma once
#include "Renderer/ShaderImplementation.h"
#include "pch.h"

namespace Core {
    class ShaderGLFW : public ShaderImplementation {
    public:
        ShaderGLFW(const std::string& vertexFile, const std::string& fragmentFile);

        void Bind() override;
        void SetIntegerUniform(const std::string& uniformName, const std::vector<int>& values) override;

        ~ShaderGLFW() override;

    private:
        unsigned int mShaderProgram{ 0 };

        std::string ReadFile(const std::string& fileName);
    };
}
