#include "WallCell.h"
#include "SteakCell.h"

void WallCell::takeDamage(Cell &owner) {
  mHP--;
  if (mHP <= 0) {owner.setImpl(std::make_unique<SteakCell>()); }
}