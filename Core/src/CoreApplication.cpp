#include "../headers/CoreApplication.h"
#include "../headers/pch.h"

namespace Core {
    void CoreApplication::Initialize() {
    }

    void CoreApplication::Update() {
    }

    void CoreApplication::Shutdown() {
    }

    void CoreApplication::Run() {
        Initialize();

        while(true){
            Update();
        }

        Shutdown();
    }
}
