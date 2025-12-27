#include "pch.h"
#include "KeyEvent.h"

namespace Core {

    KeyEvent::KeyEvent( int keyCode, KeyAction action): mKeyCode(keyCode), mKeyAction(action){}

    KeyAction KeyEvent::GetKeyAction() const {
        return mKeyAction;

    }

    int KeyEvent::GetKeyCode() const {
        return mKeyCode;
    }

    void KeyEvent::SetKeyAction(KeyAction newAction) {
        mKeyAction = newAction;
    }

    void KeyEvent::SetKeyCode(int newCode) {
        mKeyCode = newCode;
    }

}