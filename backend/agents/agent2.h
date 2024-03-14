#pragma once
#include "../../library/include/agent.h"
class Agent2: public Agent {
private:
    //function
    void writeGoodbye(int sender);
    void allDone(int sender);
public:
    Agent2(int id): Agent(id) {};
    void registerFunctions() override;
};
