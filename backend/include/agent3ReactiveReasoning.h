#pragma once
#include "../../library/include/reactiveReasoning.h"

class Agent3ReactiveReasoning : public ReactiveReasoning {
private:
    //function
    void writeGoodbye(int pSender, SimTime_t pExecTime);
    void allDone(int pSender, SimTime_t pExecTime);
public:
    void registerFunctions() override;
};