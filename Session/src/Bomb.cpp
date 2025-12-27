#include "Bomb.h"
#include <cmath>

constexpr int TILE_SIZE = 64;

Bomb::Bomb(double startX, double startY, double targetX, double targetY,
           double speed)
    : mX(startX), mY(startY), mTargetX(targetX), mTargetY(targetY),
      mSpeed(speed) {
  double dx = targetX - startX;
  double dy = targetY - startY;
  double distance = std::sqrt(dx * dx + dy * dy);

  if (distance > 0.0) {
    mVx = (dx / distance) * speed;
    mVy = (dy / distance) * speed;
  } else {
    mVx = mVy = 0.0;
  }
}

void Bomb::update() {
  double dx = mTargetX - mX;
  double dy = mTargetY - mY;
  double distanceToTarget = std::sqrt(dx * dx + dy * dy);

  // Stop if close enough to target
  if (distanceToTarget < mSpeed / 60.0) {
    mX = mTargetX;
    mY = mTargetY;
    mVx = mVy = 0.0;
  } else {
    mX += mVx / 60.0;
    mY += mVy / 60.0;
  }
}

int Bomb::getGridX() const { return static_cast<int>(mX / TILE_SIZE); }

int Bomb::getGridY() const { return static_cast<int>(mY / TILE_SIZE); }

bool Bomb::hasReachedTarget() const {
  return std::abs(mX - mTargetX) < 1.0 && std::abs(mY - mTargetY) < 1.0;
}