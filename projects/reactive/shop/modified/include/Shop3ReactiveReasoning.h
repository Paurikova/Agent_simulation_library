#pragma once
#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"
#include <iostream>

class Shop3ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int shopping = 5;
    StateShop* stateShop = nullptr;
    //functions
    void addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void open(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Shop3ReactiveReasoning(int pShopping, StateShop* pStateShop, Logger* pLogger) : ReactiveReasoning(pLogger), shopping(pShopping), stateShop(pStateShop) {}
};
