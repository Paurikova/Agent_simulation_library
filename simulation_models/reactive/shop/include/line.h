#pragma once
#include <cstdlib> // For rand()

#include "../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

class Line : public ReactiveReasoning {
private:
    StateShop* stateShop;

    std::queue<SimTime_t>& chooseLine();
    // Function handlers
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerFunctions() override;

public:
    Line(StateShop* pState, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pState) {};
};