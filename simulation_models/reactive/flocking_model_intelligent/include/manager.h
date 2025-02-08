#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "include/reactiveReasoning.h"
#include "state_bird.h"

class Manager : public ReactiveReasoning {
private:

    int number_of_birds;
    std::vector<StateBird*> birds;
    // Create an SFML window
    sf::RenderWindow& window;
    sf::CircleShape shape;


    //function
    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerFunctions() override;

public:
    Manager(int number_of_birds, sf::RenderWindow& window, Logger* logger)
            : ReactiveReasoning(logger), window(window), number_of_birds(number_of_birds) {
        // Initialize shape
        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5);  // Center the shape at its origin
        birds.resize(number_of_birds);
    };
    void initMessage();
};