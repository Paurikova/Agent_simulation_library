#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class line_manager : public ReactiveReasoning {
private:
    int arr[2] = {0, 0};
    //function
    void addToLine(int pSender, SimTime_t pExecTime);
    void hasCustomer1(int pSender, SimTime_t pExecTime);
    void hasCustomer2(int pSender, SimTime_t pExecTime);
    void removeFromLine1(int pSender, SimTime_t pExecTime);
    void removeFromLine2(int pSender, SimTime_t pExecTime);
    void registerFunctions() override;
};