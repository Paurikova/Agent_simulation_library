#pragma once
//TODO include
#include "../../../../../library/include/petriNetReasoning.h"

class Line5PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t removeFromLine_fun1_fun234(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code230(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code226(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t removeFromLine_fun2_fun238(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond221(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond216(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addToLine_fun2_fun213(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t addToLine_fun1_fun210(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond205(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
};
