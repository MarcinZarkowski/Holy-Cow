//
// Created by Marcin Zarkowski on 12/22/25.
//

#include "Bullet.h"
#include <cmath>

// Constructor: Calculate velocity vector to aim at target
Bullet::Bullet(float startX, float startY, float targetX, float targetY,
               float speed, int sourceTileX, int sourceTileY) {
  mX = startX;
  mY = startY;
  mSourceTileX = sourceTileX;
  mSourceTileY = sourceTileY;

  // Calculate direction vector
  float dx = targetX - startX;
  float dy = targetY - startY;
  float length = std::sqrt(dx * dx + dy * dy);

  // Normalize and scale by speed to get velocity (pixels per second)
  if (length > 0.0f) {
    mVx = (dx / length) * speed;
    mVy = (dy / length) * speed;
  } else {
    mVx = speed;
    mVy = 0.0f;
  }
}

// Update position based on time elapsed
void Bullet::update(float deltaTime) {
  // Move bullet: position += velocity * time
  mX += mVx * deltaTime;
  mY += mVy * deltaTime;
}