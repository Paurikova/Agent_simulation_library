#include "../include/agentManager.h"

AgentManager::AgentManager(AgentReasoning *pAgentReasoning, Logger* pLogger) :
    Agent(SIMULATION_CORE_ID, nullptr, pAgentReasoning) {}

void AgentManager::initialization() {
    Agent::initialization();
    agentReasoning->initMessage();
}