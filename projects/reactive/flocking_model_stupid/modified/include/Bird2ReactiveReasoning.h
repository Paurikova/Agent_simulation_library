#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <cmath>
#include <SFML/Graphics.hpp>
#include <random>

#include "../../../../../library/include/reactiveReasoning.h"
#include "state_bird.h"


class Bird2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateBird* birdState = nullptr;
    //functions
    void setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Bird2ReactiveReasoning(Logger* logger) : ReactiveReasoning(logger){
            // Randomly initialize position and velocity
            birdState = new StateBird(static_cast<float>(rand() % 500), static_cast<float>(rand() % 500),
                                      static_cast<float>(rand() % 2) * 2 - 1, static_cast<float>(rand() % 2) * 2 - 1);
    }
};