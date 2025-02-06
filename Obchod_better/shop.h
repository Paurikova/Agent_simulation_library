#pragma once
#include "../library/include/reactiveReasoning.h"
#include "state.h"
#include <iostream>

class Shop : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    int shopping;
    State* custInLines[2];
    //functions
    void open(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void endShoppingTime(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void registerFunctions() override;
public:
    Shop(int pShopping, State* state1, State* state2, Logger* pLogger) : ReactiveReasoning(pLogger), shopping(pShopping) {
        custInLines[0] = state1;
        custInLines[1] = state2;
    }
};