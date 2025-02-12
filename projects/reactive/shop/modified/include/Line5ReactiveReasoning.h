#pragma once
#include <cstdlib> // For rand()

#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

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
public:
    Line5ReactiveReasoning(StateShop* pState, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pState) {};
};
