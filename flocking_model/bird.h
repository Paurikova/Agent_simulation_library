#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <cmath>
#include <SFML/Graphics.hpp>
#include <random>  // For better randomness

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

    // Static random number generator and distribution
    static std::mt19937 gen;  // Mersenne Twister generator
    static std::uniform_real_distribution<float> distPos;  // For position (0 to 500)
    static std::uniform_real_distribution<float> distVel;  // For velocity (-1 to 1)


    //function
    NodeId_t getPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t setPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t draw(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void registerServices() override;
    void registerNodes() override;
public:
    Bird(sf::RenderWindow& window) : window(window) {
        // Initialize position and velocity using random distributions
//        x = distPos(gen);   // Random position between 0 and 500
//        y = distPos(gen);   // Random position between 0 and 500
//        velX = distVel(gen);  // Random velocity between -1 and 1
//        velY = distVel(gen);  // Random velocity between -1 and 1
// Randomly initialize position and velocity
        x = static_cast<float>(rand() % 500);  // Width of window
        y = static_cast<float>(rand() % 500);  // Height of window
        velX = static_cast<float>(rand() % 2) * 2 - 1;  // Random velocity between -1 and 1
        velY = static_cast<float>(rand() % 2) * 2 - 1;

        // Initialize shape
        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5);  // Center the shape at its origin
    }

//    // Static initialization for random number generation
//    static void initializeRandomGenerator() {
//        std::random_device rd;  // Random hardware-based seed
//        gen.seed(rd());         // Seed the random generator with the device
//    }
};