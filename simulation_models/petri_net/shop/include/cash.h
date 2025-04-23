#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector

#include "state_shop.h"
#include "state_break.h"
#include "../../../../library/include/petriNetReasoning.h"

class Cash : public PetriNetReasoning {
private:
    StateShop* stateShop;
    int processLength1;
    int processLength2;
    bool hasCustom1 = false;
    bool hasCustom2 = false;
    //function
    NodeId_t acceptCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer_cond2(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
public:
    Cash(int pProcessLength1, int pProcessLength2, StateShop* pStateShop, Logger* pLogger) :
            ReactiveReasoning(pLogger),  processLength1(pProcessLength1),
            processLength2(pProcessLength2), stateShop(pStateShop) {}
};