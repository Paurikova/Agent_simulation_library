#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>

#include "../library/include/petriNetReasoning.h"

class Manager : public PetriNetReasoning {
private:
    //function
    NodeId_t neighbors(std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);

    void registerServices() override;
    void registerNodes() override;
public:
    Bird(float pScreenX, float pScreenY) : screenX(pScreenX), screenY(pScreenY) {
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