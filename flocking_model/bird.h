#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <cmath>
#include <SFML/Graphics.hpp>

#include "../library/include/petriNetReasoning.h"

class Bird : public PetriNetReasoning {
private:
    float x, y; //position
    float velX, velY; //velocity
    float speed;
    float cohere_factor, separation, separate_factor, match_factor, visual_distance;
    sf::CircleShape shape;
    // Create an SFML window
    sf::RenderWindow& window;
    //function
    NodeId_t getPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t setPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t draw(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void registerServices() override;
    void registerNodes() override;
public:
    Bird(sf::RenderWindow& window) : window(window) {
        // Initialize position and velocity
        x = static_cast<float>(rand() % 500);  // Random position
        y = static_cast<float>(rand() % 500);
        velX = static_cast<float>(rand() % 2) * 2 - 1;  // Random velocity
        velY = static_cast<float>(rand() % 2) * 2 - 1;

        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5);  // Center the shape at its origin
    }
};

