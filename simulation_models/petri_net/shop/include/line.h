#pragma once
#include <cstdlib> // For rand()

#include "../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"

class Line : public PetriNetReasoning {
private:
    StateShop* stateShop;
    //function
    NodeId_t addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerNodes() override;
    void registerServices() override;
public:
    Line(StateShop* pState, Logger* pLogger) : PetriNetReasoning(pLogger), stateShop(pState) {};
};