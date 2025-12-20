#pragma once

namespace Core {
    class ShaderImplementation {
    public:
        virtual void Bind() = 0;
        virtual void SetIntegerUniform(const std::string& uniformName, const std::vector<int>& values) = 0;
        virtual ~ShaderImplementation() = default;
    };
}