#pragma once
#include <cstdlib> // For rand()

#include "../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

class Customer : public ReactiveReasoning {
private:
    StateShop* stateShop;
    //function
    void createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerFunctions() override;
public:
    Customer(StateShop* pStateShop, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pStateShop) {};
};