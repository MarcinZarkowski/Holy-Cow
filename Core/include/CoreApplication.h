#pragma once

constexpr int DEFAULT_UPDATE_INTERVAL{60};

#include "utils.h"
#include "pch.h"
#include "KeyEvent.h"
#include "WindowEvent.h"

namespace Core {

    class CORE_API CoreApplication {
    public:
        CoreApplication();

        virtual void Initialize();

        virtual void Update();

        virtual void Shutdown();

        virtual bool GameShouldClose();

        void Run();

        void SetFrameInterval(int newUpdateRate);

        void SetKeyCallback(const std::function<void( const KeyEvent& )>&);

        void SetWindowCallback(const std::function<void( const WindowEvent& )>& );

        void DefaultWindowEventHandler(const WindowEvent&);

    private:

        std::chrono::milliseconds mUpdateInterval{ std::chrono::milliseconds{1000} / DEFAULT_UPDATE_INTERVAL};
        std::chrono::steady_clock::time_point mNextFrameTime;

        bool mWindowShouldClose{false};
    };
}