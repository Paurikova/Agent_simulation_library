#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "../library/include/petriNetReasoning.h"

class Manager : public PetriNetReasoning {
private:
    float speed;
    float cohere_factor;
    float separation;
    float separate_factor;
    float match_factor;
    float visual_distance;
    int number_of_birds;
    std::vector<std::unordered_map<std::string, variant_t>> birds;
    int updatedPosition = 0;
    bool initRun = true;
    int curBirdId = 2;
    // Create an SFML window
    sf::RenderWindow& window;

    //function
    void normalize_velocity(float& velX, float& velY);
    float distance_to(float x1, float y1, float x2, float y2);
    void calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY);
    NodeId_t update_positions(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t initialization(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t move(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t handle_events(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t clearScreen(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t display(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    NodeId_t isWindowOpen(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void registerServices() override;
    void registerNodes() override;

public:
    Manager(float speed, float cohere_factor, float separation, float separate_factor,
            float match_factor, float visual_distance, int number_of_birds, sf::RenderWindow& window)
            : window(window), speed(speed), cohere_factor(cohere_factor), separation(separation),
              separate_factor(separate_factor), match_factor(match_factor),
              visual_distance(visual_distance), number_of_birds(number_of_birds) {
        birds.resize(number_of_birds);
    };
    void initMessage();
};