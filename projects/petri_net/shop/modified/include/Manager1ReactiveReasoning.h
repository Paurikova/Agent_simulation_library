#pragma once
#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int newCust = 1;
    bool run = true;
    //functions
    void closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Manager1ReactiveReasoning(int pNewCust, Logger* pLogger) : ReactiveReasoning(pLogger),
                                             newCust(pNewCust) {}

    void initMessage() override;
};
