#pragma once
#include <cstdlib> // For rand()

#include "../../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"
#include "state_break.h"

class Line5PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t hasCustomer_fun1_fun363(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond358(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromShop_fun355(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromLine_fun352(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addToLine_fun1_fun349(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond344(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Line5PetriNetReasoning(StateShop* pState, Logger* pLogger) : PetriNetReasoning(pLogger), stateShop(pState) {};
};
