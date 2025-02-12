#pragma once
//TODO incluce
#include "library/include/reactiveReasoning.h"

class Customer2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
