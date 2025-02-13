#pragma once
#include <cstdlib> // For rand()

#include "../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"
#include "state_break.h"

class Line : public PetriNetReasoning {
private:
    StateShop* stateShop;
    //function
    NodeId_t addToLine_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addToLine_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t hasCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t hasCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerNodes() override;
    void registerServices() override;
public:
    Line(StateShop* pState, Logger* pLogger) : PetriNetReasoning(pLogger), stateShop(pState) {};
};