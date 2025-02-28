#include "../include/agentManager.h"

AgentManager::AgentManager(AgentReasoning *pAgentReasoning, Logger* pLogger) :
    Agent(SIMULATION_CORE_ID, nullptr, pAgentReasoning) {
    simCore = std::make_unique<SimulationCore>(pLogger);
    simCore->registerAgent(this);
}

void AgentManager::initialization() {
    Agent::initialization();
    agentReasoning->initMessage();
    simCore->receiveAgentMessages(this);
}

void AgentManager::runSimulation(int numberOfReplications, int lengthOfReplication) {
    simCore->runSimulation(numberOfReplications, lengthOfReplication);
}

void AgentManager::registerAgent(Agent* pAgent) {
    simCore->registerAgent(pAgent);
}
void AgentManager::unregisterAgent(int agentId) {
    simCore->unregisterAgent(agentId);
}

int AgentManager::getAgentsSize() {
    return simCore->getAgentsSize();
}
Agent* AgentManager::getAgent(int position) {
    return simCore->getAgent(position);
}