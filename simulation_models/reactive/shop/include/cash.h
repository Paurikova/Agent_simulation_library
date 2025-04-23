#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector

#include "state_shop.h"
#include "../../../../library/include/reactiveReasoning.h"

class Cash : public ReactiveReasoning {
private:
    StateShop* stateShop;
    int processLength1;
    int processLength2;
    bool hasCustom1 = false;
    bool hasCustom2 = false;

    // Function declarations
    int hasBreak(int value, int cash);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;

public:
    Cash(int pProcessLength1, int pProcessLength2, StateShop* pStateShop, Logger* pLogger) :
            ReactiveReasoning(pLogger),  processLength1(pProcessLength1),
            processLength2(pProcessLength2), stateShop(pStateShop) {}
};