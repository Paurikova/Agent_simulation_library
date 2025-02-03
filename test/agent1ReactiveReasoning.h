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
    void acceptCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void generateCustomer(int pSender, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
