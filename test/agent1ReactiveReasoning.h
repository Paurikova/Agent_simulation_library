#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int newCust = 0;
    int end = 0;
    //functions
    void acceptCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void generateCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
