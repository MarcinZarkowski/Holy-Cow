#pragma once
#include "../CellImplementation.h"
#include <memory>
#include "../Cell.h"


// haystack takes damage for player, and hides them from turrets
// so user is not seen by turrets when hiding in the haystack
class HayStackCell : public CellImplementation {
    public:
        CellType getType() const override { return CellType::HayStack; }
        void takeDamage(Cell &owner) override ;
        bool isWalkable() const override { return true; }
    private:
        int mHP = 1;
};
