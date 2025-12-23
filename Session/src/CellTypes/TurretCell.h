#pragma once
#include "../CellImplementation.h"
#include <chrono>

// Turret cell - shoots at player with cooldown
class TurretCell : public CellImplementation {
private:
  std::chrono::steady_clock::time_point mLastShotTime;
  const int mFireRateMs = 2000; // Fire every 2 seconds

public:
  TurretCell() : mLastShotTime(std::chrono::steady_clock::now()) {}

  CellType getType() const override { return CellType::Turret; }
  void takeDamage(Cell &owner) override {} // Turrets don't take damage (yet)
  bool isWalkable() const override { return false; }

  // Check if enough time has passed to shoot again
  bool canShoot() override {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        now - mLastShotTime);
    if (elapsed.count() >= mFireRateMs) {
      mLastShotTime = now;
      return true;
    }
    return false;
  }
};
