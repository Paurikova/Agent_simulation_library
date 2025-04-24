#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int newCust = 10;
    int run = true;
    //functions
    void closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
