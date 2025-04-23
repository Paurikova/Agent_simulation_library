#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Shop3ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int shopping = 15;
    StateShop* stateShop = nullptr;
    //functions
    void addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void close(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void open(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
