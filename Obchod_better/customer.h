#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class Customer : public ReactiveReasoning {
private:
    int nCustomers = 0;
    //function
    void createCustomer(int pSender, int pReceiver, SimTime_t pExecTime);
    void registerFunctions() override;
};