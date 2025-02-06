#pragma once
#include <cstdlib> // For rand()

#include "../library/include/reactiveReasoning.h"
#include "state.h"

class Line : public ReactiveReasoning {
private:
    State* state;
    //function
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);
    void hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args);

    void registerFunctions() override;
public:
    Line(State* state, Logger* pLogger) : ReactiveReasoning(pLogger), state(state) {};
};