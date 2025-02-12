#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector

#include "state_shop.h"
#include "state_break.h"
#include "../../../../../library/include/petriNetReasoning.h"


using namespace std;

class Cash6PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    bool hasCustom = false;
    int processLength = 60;
    int breakLength = 100;
    std::vector<int> breaks;
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t endCustomer_fun389(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t processCustomer_fun386(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomerFun2_fun383(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer_fun1_fun380(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond375(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code371(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond366(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Cash6PetriNetReasoning(std::vector<int> pBreaks, int pBreakLength, int pProcessLength, StateShop* pStateShop, Logger* pLogger) :
    PetriNetReasoning(pLogger), breaks(pBreaks), breakLength(pBreakLength), processLength(pProcessLength),
    stateShop(pStateShop) {}
};
