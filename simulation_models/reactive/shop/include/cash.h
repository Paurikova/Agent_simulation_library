#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector

#include "state_shop.h"
#include "../../../../library/include/reactiveReasoning.h"

class Cash : public ReactiveReasoning {
private:
    StateShop* stateShop;
    std::vector<int> breaks;
    int breakLength;
    int processLength;
    bool hasCustom = false;
    int hasBreak(int value);
    //function
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Cash(std::vector<int> pBreaks, int pBreakLength, int pProcessLength, StateShop* pStateShop, Logger* pLogger) :
    ReactiveReasoning(pLogger), breaks(std::move(pBreaks)), breakLength(pBreakLength), processLength(pProcessLength),
    stateShop(pStateShop) {}
    ~Cash() {
        breaks.clear();
    }
};