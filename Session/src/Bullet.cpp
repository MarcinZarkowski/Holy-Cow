#include "Bullet.h"
#include <cmath>

Bullet::Bullet(float startX, float startY, float targetX, float targetY,
               float speed, int sourceTileX, int sourceTileY) {
  mX = startX;
  mY = startY;
  mSourceTileX = sourceTileX;
  mSourceTileY = sourceTileY;

  float dx = targetX - startX;
  float dy = targetY - startY;
  float length = std::sqrt(dx * dx + dy * dy);

  if (length > 0.0f) {
    mVx = (dx / length) * speed;
    mVy = (dy / length) * speed;
  } else {
    mVx = speed;
    mVy = 0.0f;
  }
}

void Bullet::update(float deltaTime) {
  mX += mVx * deltaTime;
  mY += mVy * deltaTime;
}