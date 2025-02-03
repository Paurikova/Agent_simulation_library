#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"

class Line : public ReactiveReasoning {
private:
    int custInLine = 0;
    //function
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);
    void getCountOfCustInLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args);

    void registerFunctions() override;
};