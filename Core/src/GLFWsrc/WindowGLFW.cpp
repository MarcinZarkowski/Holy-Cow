
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

void WindowGLFW::SetMouseCallback(
    const std::function<void(const MouseEvent &)> &newCallback) {
  mCallbacks.MouseCallback = newCallback;

  // Set up GLFW mouse button callback
  glfwSetMouseButtonCallback(
      mWindowPtr, [](GLFWwindow *window, int button, int action, int mods) {
        CallbackFunctions *callbacks{
            (CallbackFunctions *)glfwGetWindowUserPointer(window)};

        MouseEvent coreEvent;

        // Set button
        if (button == GLFW_MOUSE_BUTTON_LEFT)
          coreEvent.SetButton(MouseButton::Left);
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
          coreEvent.SetButton(MouseButton::Right);
        else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
          coreEvent.SetButton(MouseButton::Middle);

        // Set action
        if (action == GLFW_PRESS)
          coreEvent.SetAction(MouseAction::Press);
        else if (action == GLFW_RELEASE)
          coreEvent.SetAction(MouseAction::Release);

        // Get mouse position
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        coreEvent.SetPosition(xpos, ypos);

        callbacks->MouseCallback(coreEvent);
      });

  // Set up GLFW cursor position callback
  glfwSetCursorPosCallback(
      mWindowPtr, [](GLFWwindow *window, double xpos, double ypos) {
        CallbackFunctions *callbacks{
            (CallbackFunctions *)glfwGetWindowUserPointer(window)};

        MouseEvent coreEvent;
        coreEvent.SetButton(MouseButton::None);
        coreEvent.SetAction(MouseAction::Move);
        coreEvent.SetPosition(xpos, ypos);

        callbacks->MouseCallback(coreEvent);
      });
}

void WindowGLFW::HideCursor(bool hide) {
  if (mWindowPtr) {
    if (hide) {
      glfwSetInputMode(mWindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    } else {
      glfwSetInputMode(mWindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
  }
}

} // namespace Core