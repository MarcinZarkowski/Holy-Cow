#pragma once
#include "utils.h"

namespace Core {

    class CORE_API CoreApplication {
    public:
        virtual void Initialize();

        virtual void Update();

        virtual void Shutdown();

        void Run();

    private:

    };
}