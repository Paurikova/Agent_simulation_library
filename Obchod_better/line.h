#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class Line : public ReactiveReasoning {
private:
    int custInLine = 0;
    //function
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime);
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime);
    void removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime);

    void registerFunctions() override;
};