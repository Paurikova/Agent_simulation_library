#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent3ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int shopping = 1;
    int nCustomers = 0;
    //functions
    void open(int pSender, SimTime_t pExecTime);
    void removeCustomer(int pSender, SimTime_t pExecTime);
    void close(int pSender, SimTime_t pExecTime);
    //registration
    void registerFunctions() override;
};
