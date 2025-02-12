#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int newCust = 1;
    bool run = true;
    //functions
    void closeSimulation(int pSender, SimTime_t pExecTime, State* state);
    void generateCustomer(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
