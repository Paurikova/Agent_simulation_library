#pragma once
#include <unordered_map>
#include "agent.h"
#include "message.h"

const int SIMULATION_STEP = 1;

class ManagerAgent : Agent{
private:
    int currTime;
    int endTime;
    std::unordered_map<int, Agent*> agents;

public:
    ManagerAgent(int startTime, int endTime);
    void registerAgent(Agent* agent);
    void unregisterAgent(int agentId);
    void runSimulation();
private:
    //function
    void allDone(int sender);

    void registerFunctions() override;
    void registerAllFunctions();
    void initSimulation();
    void runTick();
};
