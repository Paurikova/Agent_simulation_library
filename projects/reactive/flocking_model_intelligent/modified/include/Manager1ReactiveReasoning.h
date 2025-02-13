#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "../../../../../library/include/reactiveReasoning.h"
#include "state_bird.h"

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    sf::CircleShape shape;
    sf::RenderWindow &window;
    std::vector<StateBird *> birds;
    int number_of_birds = 300;

    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    //registration
    void registerFunctions() override;

public:
    void initMessage() override;

    Manager1ReactiveReasoning(int number_of_birds, sf::RenderWindow &window, Logger *logger)
            : ReactiveReasoning(logger), window(window), number_of_birds(number_of_birds) {
        // Initialize shape
        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5);  // Center the shape at its origin
        birds.resize(number_of_birds);
    };
};
