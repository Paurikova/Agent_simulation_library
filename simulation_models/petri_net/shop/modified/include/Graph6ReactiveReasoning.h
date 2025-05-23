#pragma once
#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Graph6ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    std::string names[5] = {"in_shop", "in_line1", "in_line2", "t_line1", "t_line2"};
    StateShop* stateShop = nullptr;
    sf::RenderWindow& window;
    int showStep = 0;
    sf::Font font;
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
    void drawBarChart(std::vector<float>& data);
public:
    Graph6ReactiveReasoning(int showStep, sf::RenderWindow& window, StateShop* pStateShop, Logger* logger) : ReactiveReasoning(logger),
                                                                                                             showStep(showStep), window(window), stateShop(pStateShop) {
        // Load the font once during initialization
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
            std::cerr << "Failed to load DejaVuSans font!" << std::endl;
        }
    };
};
