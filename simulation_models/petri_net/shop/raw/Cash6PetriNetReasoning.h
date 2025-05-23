#pragma once
//TODO include
#include "library/include/petriNetReasoning.h"

class Cash6PetriNetReasoning : public PetriNetReasoning {
private:
    //attributes
    bool hasCustom2 = false;
    bool hasCustom1 = false;
    int processLength2 = 25;
    int processLength1 = 30;
    StateShop* stateShop = nullptr;
    //nodes
    NodeId_t endCustomer_fun1_fun321(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code316(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code313(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond308(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t processCustomer_fun2_fun305(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t processCustomer_fun1_fun302(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond296(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code292(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Code_code288(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond283(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t acceptCustomer_fun2_fun280(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t scceptCustomer_fun1_fun277(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    NodeId_t Condition_cond272(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void registerNodes() override;
    void registerServices() override;
};
