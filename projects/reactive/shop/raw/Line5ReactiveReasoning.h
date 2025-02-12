#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Line5ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void hasCustomer(int pSender, SimTime_t pExecTime, State* state);
    void removeFromShop(int pSender, SimTime_t pExecTime, State* state);
    void removeFromLine(int pSender, SimTime_t pExecTime, State* state);
    void addToLine(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
