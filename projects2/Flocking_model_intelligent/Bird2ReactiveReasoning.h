#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Bird2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    float speed = 3.0;
    float cohere_factor = 0.1;
    float separation = 2.0;
    float separate_factor = 0.25;
    float match_factor = 0.04;
    float visual_distance = 50;
    int number_of_birds = 300;
    int N = 0;
    BirdState* birdState = nullptr;
    StateMove* stateMove = new StateMove();
    //functions
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startMove(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void isNeighbout(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
