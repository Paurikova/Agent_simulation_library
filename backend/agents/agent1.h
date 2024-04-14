#pragma once
#include "../../library/include/agent.h"
#include <functional>

class Agent1: public Agent {
private:
    int counter = 1;
private:
    //functions
    void writeHello(int sender);
    void allDone(int sender);
public:
    Agent1(AgentId_t pId, Agent* pParent): Agent(pId, pParent) {};
    void registerFunctions() override;
};
