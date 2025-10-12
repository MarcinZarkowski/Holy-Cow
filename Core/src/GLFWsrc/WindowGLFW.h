#pragma once
#include "../../headers/WindowImplementation.h"

namespace Core {

    class WindowGLFW : public WindowImplementation {
    public:
        void CreateWindow(std::string name, int width, int height) override;
        int GetHeight() const override;
        int GetWidth() const override;
    private:

    };
}
