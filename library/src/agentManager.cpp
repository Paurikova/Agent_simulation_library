#include "../include/agentManager.h"

AgentManager::AgentManager(AgentReasoning *pAgentReasoning, Logger* pLogger) :
    Agent(MAIN_AGENT_ID, nullptr, pAgentReasoning) {}

void AgentManager::initialization() {
    Agent::initialization();
    agentReasoning->initMessage();
}