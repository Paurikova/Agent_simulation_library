#pragma once
#include <cstdlib> // For rand()

#include "../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

class Line : public ReactiveReasoning {
private:
    StateShop* stateShop;
    //function
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerFunctions() override;
public:
    Line(StateShop* pState, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pState) {};
};