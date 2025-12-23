#include "CoreApplication.h"

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "pch.h"
#include "CoreWindow.h"
#include "Renderer/Image.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "KeyEvent.h"
#include "KeyCodes.h"

namespace Core {

    CoreApplication::CoreApplication() {
        CoreWindow::Init();
        CoreWindow::GetWindow()->CreateWindow("Test", 800, 600);

        SetWindowCallback([this](const WindowEvent& event){DefaultWindowEventHandler(event);});

        Renderer::Init();
    }

    void CoreApplication::Initialize() {
    }

    void CoreApplication::Update() {
    }

    void CoreApplication::Shutdown() {
    }

    bool CoreApplication::GameShouldClose() { return mWindowShouldClose; }

    void CoreApplication::Run() {
        Initialize();

        mNextFrameTime = std::chrono::steady_clock::now() + mUpdateInterval;

        while(!GameShouldClose() && !mWindowShouldClose) {
            Renderer::GetRenderer()->ClearScreen();

            Update();

            std::this_thread::sleep_until(mNextFrameTime);

            CoreWindow::GetWindow()->SwapBuffers();
            CoreWindow::GetWindow()->PollEvents();

            mNextFrameTime = std::chrono::steady_clock::now() + mUpdateInterval;
        }

        Shutdown();
    }

    void CoreApplication::SetFrameInterval(int newUpdateRate) {
        assert(newUpdateRate > 0 and newUpdateRate < 1000);
        mUpdateInterval = std::chrono::milliseconds{1000} / newUpdateRate;
    }

    void CoreApplication::SetKeyCallback(const std::function<void( const KeyEvent& )>& newCallback){
        CoreWindow::GetWindow()->SetKeyCallback(newCallback);
    }

    void CoreApplication::SetWindowCallback(const std::function<void( const WindowEvent& )>& newCallback) {
        CoreWindow::GetWindow()->SetWindowCallback(newCallback);
    }

    void CoreApplication::DefaultWindowEventHandler(const WindowEvent &) {
        mWindowShouldClose = true;
    }


}
