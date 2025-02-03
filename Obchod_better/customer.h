#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class Customer : public ReactiveReasoning {
private:
    int nCustomers = 0;
    //function
    void createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void registerFunctions() override;
};