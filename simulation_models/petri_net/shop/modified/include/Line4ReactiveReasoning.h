#pragma once
//TODO include
#include "../../../../../library/include/reactiveReasoning.h"
#include "../include/state_shop.h"

class Line4ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //functions
    std::queue<SimTime_t>&  chooseLine();
    void removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Line4ReactiveReasoning(StateShop* pState, Logger* pLogger) : ReactiveReasoning(pLogger), stateShop(pState) {};
};
