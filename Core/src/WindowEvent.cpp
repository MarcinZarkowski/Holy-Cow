#include "WindowEvent.h"

namespace Core {

    WindowEvent::WindowEvent(WindowAction newWindowAction): mWindowAction(newWindowAction){};

    WindowAction WindowEvent::GetWindowAction() const{
        return mWindowAction;
    }

    void WindowEvent::SetWindowAction(WindowAction newWindowAction) {
        mWindowAction = newWindowAction;
    }

}