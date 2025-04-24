#pragma once
//TODO include
#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

class Customer4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Customer4ReactiveReasoning(StateShop* pStateShop, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pStateShop) {};
};
