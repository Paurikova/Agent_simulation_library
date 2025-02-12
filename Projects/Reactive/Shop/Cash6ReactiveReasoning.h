#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Cash6ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    bool hasCustom = false;
    int processLength = 30;
    int breakLength = 100;
    std::vector<int> breaks = ;
    StateShop* stateShop = nullptr;
    //functions
    void endCustomer(int pSender, SimTime_t pExecTime, State* state);
    void processCustomer(int pSender, SimTime_t pExecTime, State* state);
    void acceptCustomer(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
