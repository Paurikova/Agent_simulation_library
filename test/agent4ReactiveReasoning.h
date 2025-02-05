#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int custInLine = 0;
    //functions
    void hasCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void removeFromShop(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void NremoveFromLine(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void addToLine(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    //registration
    void registerFunctions() override;
};
