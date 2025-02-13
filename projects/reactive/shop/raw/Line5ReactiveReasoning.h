#pragma once
//TODO incluce
#include "library/include/reactiveReasoning.h"

class Line5ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
