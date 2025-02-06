#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "../library/include/petriNetReasoning.h"
#include "state_bird.h"
#include "state_move.h"

class Manager : public PetriNetReasoning {
private:
    float speed;
    float cohere_factor;
    float separation;
    float separate_factor;
    float match_factor;
    float visual_distance;

    int number_of_birds;
    std::vector<StateBird*> stateBirds;
    int curBirdId = 2;

    sf::RenderWindow& window;

    void normalize_velocity(float& velX, float& velY);
    float distance_to(float x1, float y1, float x2, float y2);
    void calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY);

    //initialization
    NodeId_t initialization_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t initialization_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t initialization_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t initialization_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t isWindowOpen_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t handleEvents_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t bird_updated(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    NodeId_t clearScreen(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t display(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

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