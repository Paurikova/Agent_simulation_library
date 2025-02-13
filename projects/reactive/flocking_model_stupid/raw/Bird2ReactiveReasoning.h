#pragma once
//TODO incluce
#include "library/include/reactiveReasoning.h"

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
};
