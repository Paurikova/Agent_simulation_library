#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Line5ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
