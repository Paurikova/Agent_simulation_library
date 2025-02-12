#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Shop3ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int shopping = 5;
    StateShop* stateShop = nullptr;
    //functions
    void addCustomerToLine(int pSender, SimTime_t pExecTime, State* state);
    void removeCustomer(int pSender, SimTime_t pExecTime, State* state);
    void newCustomer(int pSender, SimTime_t pExecTime, State* state);
    void close(int pSender, SimTime_t pExecTime, State* state);
    void open(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
};
