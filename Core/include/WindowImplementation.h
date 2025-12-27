#pragma once

#include "KeyEvent.h"
#include "MouseEvent.h"
#include "WindowEvent.h"
#include "pch.h"

namespace Core {
class WindowImplementation {
public:
  virtual ~WindowImplementation() = default;

  virtual void CreateWindow(std::string name, int width, int height) = 0;
  virtual int GetHeight() const = 0;
  virtual int GetWidth() const = 0;

  virtual void SwapBuffers() = 0;
  virtual void PollEvents() = 0;

  virtual void
  SetKeyCallback(const std::function<void(const KeyEvent &)> &newCallback) = 0;
  virtual void SetWindowCallback(
      const std::function<void(const WindowEvent &)> &newCallback) = 0;
  virtual void SetMouseCallback(
      const std::function<void(const MouseEvent &)> &newCallback) = 0;
  virtual void HideCursor(bool hide) = 0;
};
} // namespace Core