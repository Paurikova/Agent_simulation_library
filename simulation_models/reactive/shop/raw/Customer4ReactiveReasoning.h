#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Customer4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
