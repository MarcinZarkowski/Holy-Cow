
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
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void WindowGLFW::CreateWindow(std::string windowName, int width, int height) {
  mWindowPtr = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);
  std::cout << "did this" << std::endl;
  if (mWindowPtr == NULL) {
    CORE_ERROR("Failed to create GLFW window\n");
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(mWindowPtr);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    CORE_ERROR("Failed to initialize GLAD\n");
  }

  glfwSetWindowUserPointer(mWindowPtr, &mCallbacks);

  glfwSetKeyCallback(mWindowPtr, [](GLFWwindow *window, int key, int scancode,
                                    int action, int modes) {
    CallbackFunctions *callbacks{
        (CallbackFunctions *)glfwGetWindowUserPointer(window)};

    KeyEvent coreEvent;
    coreEvent.SetKeyCode(key);

    if (action == GLFW_PRESS)
      coreEvent.SetKeyAction(KeyAction::Press);
    else if (action == GLFW_REPEAT)
      coreEvent.SetKeyAction(KeyAction::Repeat);
    else if (action == GLFW_RELEASE)
      coreEvent.SetKeyAction(KeyAction::Release);

    callbacks->KeyCallback(coreEvent);
  });

  glfwSetWindowCloseCallback(mWindowPtr, [](GLFWwindow *window) {
    CallbackFunctions *callbacks{
        (CallbackFunctions *)glfwGetWindowUserPointer(window)};

    WindowEvent coreEvent;
    coreEvent.SetWindowAction(WindowAction::Close);

    callbacks->WindowCallback(coreEvent);
  });
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

void WindowGLFW::SwapBuffers() { glfwSwapBuffers(mWindowPtr); }

void WindowGLFW::PollEvents() { glfwPollEvents(); }

void WindowGLFW::SetKeyCallback(
    const std::function<void(const KeyEvent &)> &newCallback) {
  mCallbacks.KeyCallback = newCallback;
}

void WindowGLFW::SetWindowCallback(
    const std::function<void(const WindowEvent &)> &newCallback) {
  mCallbacks.WindowCallback = newCallback;
}

} // namespace Core