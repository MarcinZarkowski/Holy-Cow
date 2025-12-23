#pragma once
#include "../CellImplementation.h"

// Grass cell - walkable, takes no damage
class GrassCell : public CellImplementation {
public:
  CellType getType() const override { return CellType::Walkable; }
  void takeDamage(Cell &owner) override {} // Grass doesn't take damage
  bool isWalkable() const override { return true; }
};
