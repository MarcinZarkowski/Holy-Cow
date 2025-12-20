#include "CoreApplication.h"

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "pch.h"
#include "CoreWindow.h"
#include "Renderer/Image.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"

namespace Core {
    void CoreApplication::Initialize() {
    }

    void CoreApplication::Update() {
    }

    void CoreApplication::Shutdown() {
    }

    void CoreApplication::Run() {
        CoreWindow::Init();
        CoreWindow::GetWindow()->CreateWindow("test", 800, 600);

        Renderer::Init();

        Shader shaders("../Assets/Shaders/defaultVertexShader.glsl", "../Assets/Shaders/defaultFragmentShader.glsl");
        Image pic("../Assets/Textures/board.png");

        Initialize();
        int x = 0;

        mNextFrameTime = std::chrono::steady_clock::now() + mUpdateInterval;

        while(true){
            Update();

            Renderer::GetRenderer()->ClearScreen();

            Renderer::GetRenderer()->Draw(pic, x, 100, shaders);
            x++;
            // Base::Image pi{ "image1.png"}

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

}
