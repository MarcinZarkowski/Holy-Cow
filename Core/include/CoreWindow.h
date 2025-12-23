#pragma once

#include "pch.h"
#include "utils.h"
#include "WindowImplementation.h"
#include "KeyEvent.h"

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

        void SetKeyCallback(const std::function<void(const KeyEvent&)>& newCallback);

        void SetWindowCallback(const std::function<void(const WindowEvent&)>& newCallback);

    private:
        CoreWindow();

        std::unique_ptr<WindowImplementation> mImplementation;
        inline static std::unique_ptr<CoreWindow> mInstance;
    };
}