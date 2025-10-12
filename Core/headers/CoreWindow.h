#pragma once

#include "pch.h"
#include "utils.h"
#include "WindowImplementation.h"

namespace Core {
    class CORE_API CoreWindow {
    public:
        void CreateWindow(std::string name, int width, int height);
        int GetHeight() const;
        int GetWidth() const;

    private:
        std::unique_ptr<WindowImplementation> mImplementation;
    };
}