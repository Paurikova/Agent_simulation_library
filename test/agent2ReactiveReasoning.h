#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent2ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int nCustomers = 0;
    //functions
    void createCustomer(int pSender, SimTime_t pExecTime);
    //registration
    void registerFunctions() override;
};
