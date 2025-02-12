#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Graph4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    std::string names[5] = {"in_shop", "in_line1", "in_line2", "t_line1", "t_line2"};
    StateShop* stateShop = nullptr;
    sf::RenderWindow& window = ;
    int showStep = 60;
    //functions
    void draw(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
