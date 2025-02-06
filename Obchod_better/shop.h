#pragma once
#include "../library/include/reactiveReasoning.h"
#include "state_line.h"
#include <iostream>

class Shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    int shopping;
    StateLine* custInLines[2];
    //functions
    void open(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void endShoppingTime(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Shop(int pShopping, StateLine* state1, StateLine* state2, Logger* pLogger) : ReactiveReasoning(pLogger), shopping(pShopping) {
        custInLines[0] = state1;
        custInLines[1] = state2;
    }
};