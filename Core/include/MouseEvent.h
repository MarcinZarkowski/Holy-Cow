#pragma once

namespace Core {
enum class MouseButton { Left, Right, Middle, None };

enum class MouseAction { Press, Release, Move };

class MouseEvent {
public:
  MouseEvent();
  MouseEvent(MouseButton button, MouseAction action, double x, double y);

  MouseButton GetButton() const { return mButton; }
  MouseAction GetAction() const { return mAction; }
  double GetX() const { return mX; }
  double GetY() const { return mY; }

  void SetButton(MouseButton button) { mButton = button; }
  void SetAction(MouseAction action) { mAction = action; }
  void SetPosition(double x, double y) {
    mX = x;
    mY = y;
  }

private:
  MouseButton mButton;
  MouseAction mAction;
  double mX, mY;
};
} // namespace Core
