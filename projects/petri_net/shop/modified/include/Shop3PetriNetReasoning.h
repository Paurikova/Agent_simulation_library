#pragma once
#include "../../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"
#include <iostream>

class Shop3PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    int shopping = 3;
    StateShop *stateShop = nullptr;

    //nodes
    NodeId_t addCustomerToLine_fun2_fun341(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t addCustomerToLine_fun1_fun338(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t Condition_cond333(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t removeCustomer_fun1_fun330(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t Condition_cond325(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t newCustomer_fun322(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t close_fun319(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    NodeId_t open_fun316(int pSender, int pReceiver, SimTime_t pExecTime, State *state);

    void registerNodes() override;

    void registerServices() override;

public:
    Shop3PetriNetReasoning(int pShopping, StateShop *pStateShop, Logger *pLogger) :
            PetriNetReasoning(pLogger), shopping(pShopping), stateShop(pStateShop) {}
};
