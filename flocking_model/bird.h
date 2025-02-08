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
    StateBird* birdState;

    //function
    void getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Bird(Logger* logger) : ReactiveReasoning(logger){
        // Randomly initialize position and velocity
        birdState = new StateBird(static_cast<float>(rand() % 500), static_cast<float>(rand() % 500),
                              static_cast<float>(rand() % 2) * 2 - 1, static_cast<float>(rand() % 2) * 2 - 1);
    }
};