#pragma once
#include "../CellImplementation.h"

// Destination cell (barn) - walkable endpoint
class DestinationCell : public CellImplementation {
public:
  CellType getType() const override { return CellType::Destination; }
  void takeDamage(Cell &owner) override {}
  bool isWalkable() const override { return true; }
};
