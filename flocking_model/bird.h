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
    float screenX, screenY;
    void normalize_velocity();
    float distance_to(float otherX, float otherY);
    //function
    NodeId_t getAttributes(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    NodeId_t move(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    NodeId_t isNeighbors(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    NodeId_t normalize_velocity(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void flock(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void registerServices() override;
    void registerNodes() override;
public:
    sf::CircleShape& get_shape();
    Bird(float pScreenX, float pScreenY, float speed, float cohere_factor, float separation, float separate_factor,
         float match_factor, float visual_distance) : screenX(pScreenX), screenY(pScreenY), speed(speed), cohere_factor(cohere_factor), separation(separation),
         separate_factor(separate_factor), match_factor(match_factor), visual_distance(visual_distance) {
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