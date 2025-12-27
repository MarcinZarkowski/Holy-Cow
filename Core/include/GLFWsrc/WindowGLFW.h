#pragma once
#include "WindowImplementation.h"

#define GLFW_INCLUDE_NONE
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
  void SetKeyCallback(
      const std::function<void(const KeyEvent &)> &newCallback) override;
  void SetWindowCallback(
      const std::function<void(const WindowEvent &)> &newCallback) override;
  void SetMouseCallback(
      const std::function<void(const MouseEvent &)> &newCallback) override;
  void HideCursor(bool hide) override;

private:
  struct CallbackFunctions {
    std::function<void(const KeyEvent &)> KeyCallback{[](const KeyEvent &) {}};
    std::function<void(const WindowEvent &)> WindowCallback{
        [](const WindowEvent &) {}};
    std::function<void(const MouseEvent &)> MouseCallback{
        [](const MouseEvent &) {}};
  } mCallbacks;
  GLFWwindow *mWindowPtr{nullptr};
};
} // namespace Core
