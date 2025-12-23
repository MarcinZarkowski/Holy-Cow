#pragma once

class Bullet {
public:
  // Constructor: spawn bullet at position, aimed at target
  Bullet(float startX, float startY, float targetX, float targetY, float speed,
         int sourceTileX, int sourceTileY);

  // Update bullet position based on frame time
  void update(float deltaTime);

  // Get current position in pixels
  float getPixelX() const { return mX; }
  float getPixelY() const { return mY; }

  // Get current position in grid coordinates
  int getGridX(int tileSize) const { return static_cast<int>(mX / tileSize); }
  int getGridY(int tileSize) const { return static_cast<int>(mY / tileSize); }

  // Get source turret tile (to avoid collision with own turret)
  int getSourceTileX() const { return mSourceTileX; }
  int getSourceTileY() const { return mSourceTileY; }

private:
  // Position in world pixels
  float mX, mY;

  // Velocity in pixels per second
  float mVx, mVy;

  // Source turret tile coordinates
  int mSourceTileX, mSourceTileY;
};
