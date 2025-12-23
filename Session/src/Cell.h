#pragma once
#include "CellImplementation.h"
#include <memory>

// Forward declaration
class CellImplementation;

// Cell wrapper - holds pointer to implementation
class Cell {
public:
  Cell();
  Cell(CellType type);

  // Copy/Move semantics
  Cell(const Cell &other);
  Cell &operator=(const Cell &other);
  Cell(Cell &&other) = default;
  Cell &operator=(Cell &&other) = default;

  CellType getType() const { return mImpl->getType(); }
  void takeDamage() { mImpl->takeDamage(*this); }
  bool isWalkable() const { return mImpl->isWalkable(); }
  bool canShoot() { return mImpl->canShoot(); }

  void setType(CellType type);
  void setImpl(std::unique_ptr<CellImplementation> impl) {
    mImpl = std::move(impl);
  }

private:
  std::unique_ptr<CellImplementation> mImpl;
};
