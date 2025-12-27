#include "CoreWindow.h"
#include "GLFWsrc/WindowGLFW.h"
#include "pch.h"

namespace Core {
CoreWindow::CoreWindow() {
  std::cout << "initializing window" << std::endl;
#ifdef CORE_GLFW
  std::cout << "did this, making window implementation the GLFW one"
            << std::endl;
  mImplementation = std::unique_ptr<WindowGLFW>(new WindowGLFW);
#else
#only_GLFW_is_supported
#endif
}

void CoreWindow::Init() {
  if (!mInstance)
    mInstance = std::unique_ptr<CoreWindow>{new CoreWindow};
}

std::unique_ptr<CoreWindow> &CoreWindow::GetWindow() { return mInstance; }

void CoreWindow::CreateWindow(std::string windowName, int width, int height) {
  mImplementation->CreateWindow(std::move(windowName), width, height);
}

int CoreWindow::GetHeight() const { return mImplementation->GetHeight(); }

int CoreWindow::GetWidth() const { return mImplementation->GetWidth(); }

void CoreWindow::SwapBuffers() { mImplementation->SwapBuffers(); }

void CoreWindow::PollEvents() { mImplementation->PollEvents(); }

void CoreWindow::SetKeyCallback(
    const std::function<void(const KeyEvent &)> &newCallback) {
  mImplementation->SetKeyCallback(newCallback);
}

void CoreWindow::SetWindowCallback(
    const std::function<void(const WindowEvent &)> &newCallback) {
  mImplementation->SetWindowCallback(newCallback);
}

void CoreWindow::SetMouseCallback(
    const std::function<void(const MouseEvent &)> &newCallback) {
  mImplementation->SetMouseCallback(newCallback);
}

void CoreWindow::HideCursor(bool hide) { mImplementation->HideCursor(hide); }
} // namespace Core