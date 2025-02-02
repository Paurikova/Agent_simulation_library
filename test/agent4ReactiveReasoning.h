#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int custInLine = 0;
    //functions
    void hasCustomer(int pSender, SimTime_t pExecTime);
    void removeFromShop(int pSender, SimTime_t pExecTime);
    void NremoveFromLine(int pSender, SimTime_t pExecTime);
    void addToLine(int pSender, SimTime_t pExecTime);
    //registration
    void registerFunctions() override;
};
