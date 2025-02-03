#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector

#include "../library/include/reactiveReasoning.h"

class Cash : public ReactiveReasoning {
private:
    std::vector<int> breaks;
    int breakLength;
    int processLength;
    bool hasCustom = false;
    int hasBreak(int value);
    //function
    void acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void registerFunctions() override;
public:
    Cash(std::vector<int> pBreaks, int pBreakLength, int pProcessLength) :
        breaks(pBreaks), breakLength(pBreakLength), processLength(pProcessLength) {}
};