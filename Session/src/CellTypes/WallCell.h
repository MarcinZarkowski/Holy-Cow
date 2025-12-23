#pragma once
#include "../Cell.h"
#include "../CellImplementation.h"

// Wall cell (cow) - has HP, converts to grass at 0
class WallCell : public CellImplementation {
private:
  int mHP;

public:
  WallCell() : mHP(3) {}
  CellType getType() const override { return CellType::Wall; }
  void takeDamage(Cell &owner) override;
  bool isWalkable() const override { return false; }
  int getHP() const { return mHP; }
};