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

  // Bomb system
  int getBombsRemaining() const { return mBombsRemaining; }
  bool canThrowBomb() const { return mBombsRemaining > 0; }
  void throwBomb() {
    if (mBombsRemaining > 0)
      mBombsRemaining--;
  }

private:
  std::vector<int> mTileCoords; // Stores [tileX, tileY]
  int mHealth = 3;              // Player starts with 3 HP
  bool mWon = false;
  int mBombsRemaining = 5; // Player has 5 bombs total
};
