#include "../headers/CoreApplication.h"
#include "../headers/pch.h"
#include "../headers/CoreWindow.h"

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

        Initialize();

        while(true){
            Update();

            CoreWindow::GetWindow()->SwapBuffers();
            CoreWindow::GetWindow()->PollEvents();
        }

        Shutdown();
    }
}
