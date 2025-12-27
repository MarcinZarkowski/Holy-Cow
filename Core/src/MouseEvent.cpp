#include "MouseEvent.h"

namespace Core {

MouseEvent::MouseEvent()
    : mButton(MouseButton::None), mAction(MouseAction::Move), mX(0.0), mY(0.0) {
}

MouseEvent::MouseEvent(MouseButton button, MouseAction action, double x, double y)
    : mButton(button), mAction(action), mX(x), mY(y) {}

} // namespace Core
