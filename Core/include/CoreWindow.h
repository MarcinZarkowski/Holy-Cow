#pragma once

#include "pch.h"
#include "utils.h"
#include "WindowImplementation.h"

namespace Core {
    class CORE_API CoreWindow {
    public:
        static void Init();
        static std::unique_ptr<CoreWindow>& GetWindow();

        void CreateWindow(std::string name, int width, int height);
        int GetHeight() const;
        int GetWidth() const;

        void SwapBuffers();
        void PollEvents();

    private:
        CoreWindow();

        std::unique_ptr<WindowImplementation> mImplementation;
        inline static std::unique_ptr<CoreWindow> mInstance;
    };
}