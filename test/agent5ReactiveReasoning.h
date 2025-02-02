#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent5ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int hasCustom = 1;
    int processLength = 0;
    int breakLength = 0;
    std::vector<int> breaks = {0};
    //functions
    void processCustomer(int pSender, SimTime_t pExecTime);
    void acceptCustomer(int pSender, SimTime_t pExecTime);
    //registration
    void registerFunctions() override;
};
