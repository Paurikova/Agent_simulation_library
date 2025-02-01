#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class cash_register : public ReactiveReasoning {
private:
    int arr[2][2] = {{130, 170}, {200, -1}};
    int breaking_long[2] = {30, 60};
    int customer_processing[2] = {15, 10};
    bool customers[2] = {false, false};
    int hasBreak(int cache, int value);
    //function
    void processCustomer1(int pSender, SimTime_t pExecTime);
    void processCustomer2(int pSender, SimTime_t pExecTime);
    void newCustomer1(int pSender, SimTime_t pExecTime);
    void newCustomer2(int pSender, SimTime_t pExecTime);
    void endCustomer1(int pSender, SimTime_t pExecTime);
    void endCustomer2(int pSender, SimTime_t pExecTime);
    void hasCustomer1(int pSender, SimTime_t pExecTime);
    void hasCustomer2(int pSender, SimTime_t pExecTime);
    void registerFunctions() override;
};