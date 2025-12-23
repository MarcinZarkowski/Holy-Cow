#pragma once
#include <vector>

class GameState {
public:
  GameState() = default;
  GameState(int tileX, int tileY); // Constructor takes TILE coordinates
  void setTileCoords(int tileX, int tileY);
  void moveTiles(int deltaTileX, int deltaTileY); // Move by tiles
  int getTileX() const;
  int getTileY() const;

  void setWon();

  bool Won();

  // Health system
  int getHealth() const { return mHealth; }
  void takeDamage() {
    if (mHealth > 0)
      mHealth--;
  }
  void heal() {
    if (mHealth < 3)
      mHealth++;
  }
  bool isDead() const { return mHealth <= 0; }

private:
  std::vector<int> mTileCoords; // Stores [tileX, tileY]
  int mHealth = 3;              // Player starts with 3 HP
  bool mWon = false;
};
