#include "../library/include/reactiveReasoning.h"
#include "state_shop.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <unordered_map>

class Graph : public ReactiveReasoning {
private:
    sf::RenderWindow& window;
    StateShop* stateShop;

    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Graph(sf::RenderWindow& window, Logger* logger) : ReactiveReasoning(logger), window(window) {}
    void drawBarChart(std::vector<float>& data);
};