#pragma once

constexpr int DEFAULT_UPDATE_INTERVAL{60};

#include "utils.h"
#include "pch.h"

namespace Core {

    class CORE_API CoreApplication {
    public:
        virtual void Initialize();

        virtual void Update();

        virtual void Shutdown();

        void Run();

        void SetFrameInterval(int newUpdateRate);

    private:

        std::chrono::milliseconds mUpdateInterval{ std::chrono::milliseconds{1000} / DEFAULT_UPDATE_INTERVAL};
        std::chrono::steady_clock::time_point mNextFrameTime;

    };
}