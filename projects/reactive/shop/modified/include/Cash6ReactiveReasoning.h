#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include "state_shop.h"
#include "../../../../../library/include/reactiveReasoning.h"

class Cash6ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    bool hasCustom1 = false;
    bool hasCustom2 = false;
    int processLength1 = 30;
    int processLength2 = 25;
    StateShop* stateShop = nullptr;
    //functions
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Cash6ReactiveReasoning(int pProcessLength1, int pProcessLength2, StateShop* pStateShop, Logger* pLogger) :
    ReactiveReasoning(pLogger), processLength1(pProcessLength1), processLength2(pProcessLength2),
    stateShop(pStateShop) {}
};
