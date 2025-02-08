#pragma once
#include "../../../../library/include/petriNetReasoning.h"
#include "state_shop.h"
#include <iostream>

class Shop : public PetriNetReasoning {
private:
    //attributes
    StateShop* stateShop;
    int shopping;
    //functions
    NodeId_t open(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t close(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addCustomerToLine_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addCustomerToLine_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addCustomerToLine_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Shop(int pShopping, StateShop* pStateShop, Logger* pLogger) :
    PetriNetReasoning(pLogger), shopping(pShopping), stateShop(pStateShop) {}
};