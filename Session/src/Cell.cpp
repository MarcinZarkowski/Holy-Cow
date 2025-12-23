#include "Cell.h"
#include "CellTypes/DestinationCell.h"
#include "CellTypes/GrassCell.h"
#include "CellTypes/HayStackCell.h"
#include "CellTypes/SteakCell.h"
#include "CellTypes/TurretCell.h"
#include "CellTypes/WallCell.h"

// Default constructor - creates grass
Cell::Cell() : mImpl(std::make_unique<GrassCell>()) {}

// Cell constructor - creates appropriate implementation
Cell::Cell(CellType type) {
  switch (type) {
  case CellType::Walkable:
    mImpl = std::make_unique<GrassCell>();
    break;
  case CellType::Wall:
    mImpl = std::make_unique<WallCell>();
    break;
  case CellType::Turret:
    mImpl = std::make_unique<TurretCell>();
    break;
  case CellType::Destination:
    mImpl = std::make_unique<DestinationCell>();
    break;
  case CellType::Steak:
    mImpl = std::make_unique<SteakCell>();
    break;
  case CellType::HayStack:
    mImpl = std::make_unique<HayStackCell>();
    break;
  default:
    mImpl = std::make_unique<GrassCell>();
  }
}

// Copy constructor - deep copy the implementation
Cell::Cell(const Cell &other) {
  switch (other.getType()) {
  case CellType::Walkable:
    mImpl = std::make_unique<GrassCell>();
    break;
  case CellType::Wall:
    mImpl = std::make_unique<WallCell>();
    break;
  case CellType::Turret:
    mImpl = std::make_unique<TurretCell>();
    break;
  case CellType::Destination:
    mImpl = std::make_unique<DestinationCell>();
    break;
  case CellType::Steak:
    mImpl = std::make_unique<SteakCell>();
    break;
  case CellType::HayStack:
    mImpl = std::make_unique<HayStackCell>();
    break;
  }
}

// Copy assignment
Cell &Cell::operator=(const Cell &other) {
  if (this != &other) {
    switch (other.getType()) {
    case CellType::Walkable:
      mImpl = std::make_unique<GrassCell>();
      break;
    case CellType::Wall:
      mImpl = std::make_unique<WallCell>();
      break;
    case CellType::Turret:
      mImpl = std::make_unique<TurretCell>();
      break;
    case CellType::Destination:
      mImpl = std::make_unique<DestinationCell>();
      break;
    case CellType::Steak:
      mImpl = std::make_unique<SteakCell>();
      break;
    case CellType::HayStack:
      mImpl = std::make_unique<HayStackCell>();
      break;
    }
  }
  return *this;
}

// setType - replaces implementation
void Cell::setType(CellType type) {
  switch (type) {
  case CellType::Walkable:
    mImpl = std::make_unique<GrassCell>();
    break;
  case CellType::Wall:
    mImpl = std::make_unique<WallCell>();
    break;
  case CellType::Turret:
    mImpl = std::make_unique<TurretCell>();
    break;
  case CellType::Destination:
    mImpl = std::make_unique<DestinationCell>();
    break;
  case CellType::Steak:
    mImpl = std::make_unique<SteakCell>();
    break;
  case CellType::HayStack:
    mImpl = std::make_unique<HayStackCell>();
    break;
  }
}
