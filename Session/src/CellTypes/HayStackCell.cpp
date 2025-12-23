#include "HayStackCell.h"
#include "GrassCell.h"

void HayStackCell::takeDamage(Cell &owner){
    mHP--;
    if (mHP <= 0) {owner.setImpl(std::make_unique<GrassCell>()); }
}