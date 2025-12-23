#pragma once

// Forward declaration
class Cell;

enum class CellType {
  Walkable = 0,
  Wall = 1,
  Turret = 2,
  Destination = 3,
  Steak = 4,
  HayStack = 5
};

// Abstract base class for all cell implementations
class CellImplementation {
public:
  virtual ~CellImplementation() = default;
  virtual CellType getType() const = 0;
  virtual void takeDamage(Cell &owner) = 0;
  virtual bool isWalkable() const = 0;

  // Turret-specific method (only TurretCell implements this)
  virtual bool canShoot() { return false; }
};
