#pragma once
//TODO include
#include "../../../../../library/include/reactiveReasoning.h"
#include "state_shop.h"

class Line4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    //registration
    void registerFunctions() override;
    std::queue<SimTime_t>& chooseLine();
public:
    Line4ReactiveReasoning(StateShop* pState, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pState) {};
};
