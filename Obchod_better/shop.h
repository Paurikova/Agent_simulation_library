#pragma once
#include "../library/include/reactiveReasoning.h"
#include "state_shop.h"
#include <iostream>

class Shop : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop;
    int shopping;
    //functions
    void open(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void endShoppingTime(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Shop(int pShopping, StateShop* pStateShop, Logger* pLogger) : ReactiveReasoning(pLogger), shopping(pShopping), stateShop(pStateShop) {}
};