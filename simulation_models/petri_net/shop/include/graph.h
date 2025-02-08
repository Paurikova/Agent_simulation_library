#include "../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Graph : public ReactiveReasoning {
private:
    int showStep;
    sf::RenderWindow& window;
    StateShop* stateShop;
    std::string names[5] = {"in_shop", "in_line1", "in_line2", "t_line1", "t_line2"};

    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
    void drawBarChart(std::vector<float>& data);
public:
    Graph(int showStep, sf::RenderWindow& window, StateShop* pStateShop, Logger* logger) : ReactiveReasoning(logger),
    showStep(showStep), window(window), stateShop(pStateShop) {};
};