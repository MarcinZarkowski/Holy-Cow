#pragma once
#include "../../headers/WindowImplementation.h"
#include "GLFW/glfw3.h"

namespace Core {

    class WindowGLFW : public WindowImplementation {
    public:
        WindowGLFW();
        void CreateWindow(std::string name, int width, int height) override;
        int GetHeight() const override;
        int GetWidth() const override;

        void SwapBuffers() override;
        void PollEvents() override;

    private:
        GLFWwindow* mWindowPtr { nullptr };
    };
}
