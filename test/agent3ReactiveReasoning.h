#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Agent3ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int shopping = 1;
    int nCustomers = 0;
    //functions
    void open(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void removeCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void close(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    //registration
    void registerFunctions() override;
};
