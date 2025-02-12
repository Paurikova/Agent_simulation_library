#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include "state_shop.h"
#include "../../../../../library/include/reactiveReasoning.h"

class Cash6ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    bool hasCustom = false;
    int processLength = 30;
    int breakLength = 100;
    std::vector<int> breaks;
    StateShop* stateShop = nullptr;
    int hasBreak(int value);
    //functions
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Cash6ReactiveReasoning(std::vector<int> pBreaks, int pBreakLength, int pProcessLength, StateShop* pStateShop, Logger* pLogger) :
    ReactiveReasoning(pLogger), breaks(pBreaks), breakLength(pBreakLength), processLength(pProcessLength),
    stateShop(pStateShop) {}
};
