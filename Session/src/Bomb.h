#pragma once

class Bomb {
public:
  Bomb(double startX, double startY, double targetX, double targetY,
       double speed);

  void update();
  double getPixelX() const { return mX; }
  double getPixelY() const { return mY; }
  int getGridX() const;
  int getGridY() const;
  bool hasReachedTarget() const;

private:
  double mX, mY;
  double mTargetX, mTargetY;
  double mVx, mVy;
  double mSpeed;
};