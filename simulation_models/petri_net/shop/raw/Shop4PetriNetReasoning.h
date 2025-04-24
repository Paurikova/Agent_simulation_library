#pragma once
//TODO include
#include "library/include/petriNetReasoning.h"

class Shop4PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    int shopping = 15;
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t addCustomerToLine_fun180(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_fun2_fun177(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_fun1_fun174(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond169(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t newCustomer_fun166(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t close_fun163(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t open_fun160(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
};
