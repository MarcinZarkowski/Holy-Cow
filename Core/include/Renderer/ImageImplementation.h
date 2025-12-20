#pragma once

namespace Core {
    class ImageImplementation {
    public:
        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        virtual ~ImageImplementation() = default;

        virtual void Bind() = 0;
    };
}