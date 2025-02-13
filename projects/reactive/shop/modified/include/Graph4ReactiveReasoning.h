#pragma once
#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Graph4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    std::string names[5] = {"in_shop", "in_line1", "in_line2", "t_line1", "t_line2"};
    StateShop* stateShop = nullptr;
    sf::RenderWindow& window;
    int showStep = 60;
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
    void drawBarChart(std::vector<float>& data);
public:
    Graph4ReactiveReasoning(int showStep, sf::RenderWindow& window, StateShop* pStateShop, Logger* logger) : ReactiveReasoning(logger),
                                                                                           showStep(showStep), window(window), stateShop(pStateShop) {};
};
