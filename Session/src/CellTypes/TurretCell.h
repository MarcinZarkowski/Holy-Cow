#pragma once
#include "../CellImplementation.h"
#include "GrassCell.h"
#include <chrono>

// Turret cell - shoots at player with cooldown
class TurretCell : public CellImplementation {
private:
  std::chrono::steady_clock::time_point mLastShotTime;
  const int mFireRateMs = 2000; // Fire every 2 seconds
  int mHealth = 5;              // Turrets have 5 health

public:
  TurretCell() : mLastShotTime(std::chrono::steady_clock::now()) {}

  CellType getType() const override { return CellType::Turret; }
  void takeDamage(Cell &owner) override {
    if (mHealth > 0) {
      mHealth--;
      if (mHealth == 0) {
        owner.setImpl(std::make_unique<GrassCell>());
      }
    }
  }
  bool isWalkable() const override { return false; }
  int getHealth() const { return mHealth; }

  // Check if enough time has passed to shoot again and if turret has health
  bool canShoot() override {
    if (mHealth <= 0) { // Cannot shoot if destroyed
      return false;
    }
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
