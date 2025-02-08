#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector

#include "state_shop.h"
#include "../../../../library/include/petriNetReasoning.h"

class Cash : public PetriNetReasoning {
private:
    StateShop* stateShop;
    std::vector<int> breaks;
    int breakLength;
    int processLength;
    bool hasCustom = false;
    int hasBreak(int value);
    //function
    NodeId_t acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Cash(std::vector<int> pBreaks, int pBreakLength, int pProcessLength, StateShop* pStateShop, Logger* pLogger) :
    PetriNetReasoning(pLogger), breaks(pBreaks), breakLength(pBreakLength), processLength(pProcessLength),
    stateShop(pStateShop) {}
};