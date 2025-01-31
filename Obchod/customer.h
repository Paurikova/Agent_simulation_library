#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class customer : public ReactiveReasoning {
private:
    //function
    void checkNewCustomer(int pSender, SimTime_t pExecTime);
    void registerFunctions() override;
};