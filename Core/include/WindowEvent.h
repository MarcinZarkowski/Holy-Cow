#pragma once
#include "utils.h"

namespace Core {
    enum class CORE_API WindowAction {
        None,
        Minimize,
        Maximize,
        Resize,
        Close
    };

    class CORE_API WindowEvent {

        public:
        WindowEvent() = default;
        WindowEvent(WindowAction newWindowAction);

        WindowAction GetWindowAction() const;

        void SetWindowAction(WindowAction newWindowAction);

        private:
        WindowAction mWindowAction{WindowAction::None};

    };
}