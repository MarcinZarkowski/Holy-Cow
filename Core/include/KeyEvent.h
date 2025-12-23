#pragma once

#include "utils.h"

namespace Core {
    enum class CORE_API KeyAction {
        None,
        Press,
        Release,
        Repeat
    };

    class CORE_API KeyEvent {

    public:
        KeyEvent() = default;
        KeyEvent( int keyCode, KeyAction action);
        int GetKeyCode() const;
        void SetKeyCode(int newCode);
        KeyAction GetKeyAction() const;
        void SetKeyAction(KeyAction newAction);

    private:
        int mKeyCode{ -1 };
        KeyAction mKeyAction{ KeyAction::None };
    };
}