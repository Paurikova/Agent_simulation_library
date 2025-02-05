#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent5ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int hasCustom = 1;
    int processLength = 0;
    int breakLength = 0;
    std::vector<int> breaks = {0};
    //functions
    void processCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void acceptCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    //registration
    void registerFunctions() override;
};
