#pragma once
#include "agent.h"
#include "message.h"
#include "types_library.h"
#include "../../units/include/logger.h"
#include "simulationCore.h"

class AgentManager : public Agent {
    std::unique_ptr<SimulationCore> simCore;
public:
    AgentManager(AgentReasoning* pAgentReasoning, Logger* pLogger);
    void initSimulation();
    void runSimulation(int numberOfReplications, int lengthOfReplication);
    void registerAgent(Agent* pAgent);
    void unregisterAgent(int agentId);
    int getAgentsSize();
    Agent* getAgent(int position);
};