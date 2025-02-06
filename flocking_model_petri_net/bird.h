#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <cmath>
#include <SFML/Graphics.hpp>
#include <random>  // For better randomness

#include "../library/include/reactiveReasoning.h"
#include "state_bird.h"

class Bird : public ReactiveReasoning {
private:
    StateBird* stateBird;
    float speed;
    float cohere_factor, separation, separate_factor, match_factor, visual_distance;
    sf::CircleShape shape;

    sf::RenderWindow& window;

    //function
    NodeId_t getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerFunctions() override;
public:
    Bird(sf::RenderWindow& window, Logger* pLogger) : ReactiveReasoning(pLogger), window(window) {
        // Randomly initialize position and velocity
        float x = static_cast<float>(rand() % 500);  // Width of window
        float y = static_cast<float>(rand() % 500);  // Height of window
        float velX = static_cast<float>(rand() % 2) * 2 - 1;  // Random velocity between -1 and 1
        float velY = static_cast<float>(rand() % 2) * 2 - 1;
        stateBird = new StateBird(x, y, velX, velY);
        // Initialize shape
        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5);  // Center the shape at its origin
    }
};