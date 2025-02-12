#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Customer2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void createCustomer(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
