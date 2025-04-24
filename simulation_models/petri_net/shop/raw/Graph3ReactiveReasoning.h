#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Graph3ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    std::string names[5] = {"in_shop", "in_line1", "in_line2", "t_line1", "t_line2"};
    StateShop* stateShop = nullptr;
    sf::RenderWindow& window = InitValue;
    int showStep = 0;
    sf::Dont font = ;
    //functions
    //registration
    void registerFunctions() override;
};
