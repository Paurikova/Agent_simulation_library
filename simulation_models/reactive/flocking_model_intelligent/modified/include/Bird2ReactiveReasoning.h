#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <cmath>
#include <SFML/Graphics.hpp>
#include <random>  // For better randomness

#include "../../../../../library/include/reactiveReasoning.h"
#include "state_bird.h"
#include "state_move.h"

class Bird2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateMove* stateMove = new StateMove();
    StateBird* birdState = nullptr;
    int N = 0;
    int number_of_birds = 300;
    float visual_distance = 50;
    float match_factor = 0.04;
    float separate_factor = 0.25;
    float separation = 2.0;
    float cohere_factor = 0.1;
    float speed = 3.0;

    void normalize_velocity(float& velX, float& velY);
    float distance_to(float x1, float y1, float x2, float y2);
    void calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY);

    //functions
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startMove(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void isNeighbout(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Bird2ReactiveReasoning(float speed, float cohere_factor, float separation, float separate_factor, float match_factor,
         float visual_distance, int number_of_birds, Logger* logger) : ReactiveReasoning(logger),
                                                                       speed(speed), cohere_factor(cohere_factor), separation(separation), separate_factor(separate_factor),
                                                                       match_factor(match_factor), visual_distance(visual_distance), number_of_birds(number_of_birds) {
        // Randomly initialize position and velocity
        birdState = new StateBird(static_cast<float>(rand() % 500), static_cast<float>(rand() % 500),
                                  static_cast<float>(rand() % 2) * 2 - 1, static_cast<float>(rand() % 2) * 2 - 1);
    }
};
