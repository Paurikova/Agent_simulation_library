#pragma once
#include "../backend/agent.h"
#include <functional>
class Agent1: public Agent {
private:
    int counter = 1;
private:
    //functions
    void writeHello(int sender);
    void allDone(int sender);
public:
    Agent1(int id): Agent(id) {};
    void registerFunctions() override;
};
