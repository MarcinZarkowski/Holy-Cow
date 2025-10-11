#include "Core.h"
#include<iostream>

class Game : public Core::CoreApplication {
    void Update() override {
        std::cout<<"Game is running"<<std::endl;
    }
};

START_CORE_GAME(Game);

