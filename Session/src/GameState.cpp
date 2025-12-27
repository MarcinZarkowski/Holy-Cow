#include "GameState.h"
#include <vector>

GameState::GameState(int tileX, int tileY) { mTileCoords = {tileX, tileY}; }

void GameState::setTileCoords(int tileX, int tileY) {
  mTileCoords[0] = tileX;
  mTileCoords[1] = tileY;
}

void GameState::moveTiles(int deltaTileX, int deltaTileY) {
  mTileCoords[0] += deltaTileX;
  mTileCoords[1] += deltaTileY;
}

void GameState::setWon() { mWon = true; }

bool GameState::Won() { return mWon; }

int GameState::getTileX() const { return mTileCoords[0]; }

int GameState::getTileY() const { return mTileCoords[1]; }