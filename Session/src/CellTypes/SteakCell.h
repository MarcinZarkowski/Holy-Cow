#pragma once
#include "../CellImplementation.h"

// Steak cell - walkable collectible
class SteakCell : public CellImplementation {
public:
  CellType getType() const override { return CellType::Steak; }
  void takeDamage(Cell &owner) override {}
  bool isWalkable() const override { return true; }
};
