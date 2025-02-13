#pragma once
//TODO incluce
#include "library/include/reactiveReasoning.h"

class Cash6ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    bool hasCustom = false;
    int processLength = 30;
    int breakLength = 100;
    std::vector<int> breaks = ;
    StateShop* stateShop = nullptr;
    //functions
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
