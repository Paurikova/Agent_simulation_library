#pragma once
#include "../../library/include/reactiveReasoning.h"

class Agent1ReactiveReasoning : public ReactiveReasoning {
private:
    int counter = 1;
private:
    //functions
    void writeHello(int pSender, SimTime_t pExecTime);
    void allDone(int pSender, SimTime_t pExecTime);
public:
    void registerFunctions() override;
};