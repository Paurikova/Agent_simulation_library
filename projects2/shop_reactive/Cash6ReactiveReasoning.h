#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Cash6ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    bool hasCustom2 = false;
    bool hasCustom1 = false;
    int processLength2 = 25;
    int processLength1 = 30;
    StateShop* stateShop = nullptr;
    //functions
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
