#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Bird2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateBird* birdState = nullptr;
    //functions
    void setPosition(int pSender, SimTime_t pExecTime, State* state);
    void move(int pSender, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
