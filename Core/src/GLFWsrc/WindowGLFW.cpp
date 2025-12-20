
#include "GLFWsrc/WindowGLFW.h"
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "utils.h"

namespace Core {

    WindowGLFW::WindowGLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void WindowGLFW::CreateWindow(std::string windowName, int width, int height) {
        mWindowPtr = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
        std::cout<<"did this"<<std::endl;
        if (mWindowPtr == NULL) {
            CORE_ERROR("Failed to create GLFW window\n");
        }
        glfwMakeContextCurrent(mWindowPtr);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            CORE_ERROR("Failed to initialize GLAD\n");
        }
    }

    int WindowGLFW::GetWidth() const {
        int width{0}, height{0};
        glfwGetWindowSize(mWindowPtr, &width, &height);
        return width;
    }

    int WindowGLFW::GetHeight() const {
        int width{0}, height{0};
        glfwGetWindowSize(mWindowPtr, &width, &height);
        return height;
    }

    void WindowGLFW::SwapBuffers() {
        glfwSwapBuffers(mWindowPtr);
    }

    void WindowGLFW::PollEvents() {
        glfwPollEvents();
    }
}