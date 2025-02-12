#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Bird2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateMove* stateMove = new StateMove();
    BirdState* birdState = nullptr;
    int N = 0;
    int number_of_birds = 300;
    float visual_distance = 50;
    float match_factor = 0.04;
    float separate_factor = 0.25;
    float separation = 2.0;
    float cohere_factor = 0.1;
    float speed = 3.0;
    //functions
    void move(int pSender, SimTime_t pExecTime, State* state);
    void startMove(int pSender, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, SimTime_t pExecTime, State* state);
    void isNeighbout(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
