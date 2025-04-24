#pragma once
//TODO include
#include "../../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"

class Shop4PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    int shopping = 15;
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_fun177(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_fun174(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_cond169(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t close(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t open(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Shop4PetriNetReasoning(int pShopping, StateShop* pStateShop, Logger* pLogger) :
            PetriNetReasoning(pLogger), shopping(pShopping), stateShop(pStateShop) {}
};
