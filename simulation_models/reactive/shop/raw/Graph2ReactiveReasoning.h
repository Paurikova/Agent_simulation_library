#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Graph2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    std::string names[5] = {"in_shop", "in_line1", "in_line2", "t_line1", "t_line2"};
    StateShop* stateShop = nullptr;
    sf::RenderWindow& window = InitValue;
    int showStep = 40;
    sf::Font font = InitValue;
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
