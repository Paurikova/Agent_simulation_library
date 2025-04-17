#include "../include/agent.h"

void Agent::process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t execTime, State* state) {
    agentReasoning->process(pServiceId, pSender, pReceiver, execTime, state);
}

Agent::Agent(AgentId_t pId, Agent* pParent, AgentReasoning* pAgentReasoning) {
    id = pId;
    parent = pParent;
    currTime  = -1;
    schedule = std::make_unique<Schedule>();
    if (pAgentReasoning == nullptr) {
        throw std::runtime_error(
                "Agent type is invalid.");
    }
    agentReasoning = pAgentReasoning;
    registerAsSon(pParent);
}

AgentId_t Agent::getId() const {
    return id;
}

std::map<AgentId_t, Agent*> Agent::getSons() {
    return sons;
}

void Agent::receiveMessage(Message* pMsg) {
    schedule->pushMessage(pMsg);
}

void Agent::execute() {
    Message* message = schedule->popMessage();
    while (message) {
        currTime = message->execTime;
        process(message->serviceId, message->sender, message->receiver, message->execTime, message->state);
        delete message;
        message = schedule->popMessage();
    }
}

bool Agent::providedService(ServiceId_t pServiceId) {
    return agentReasoning->providedService(pServiceId);
}

Message* Agent::getTopOutboxMessage() {
    return agentReasoning->getTopOutboxMessage();
}

void Agent::registerAsSon(Agent* pParent) {
    if (!pParent) {
        return;
    }
    pParent->registerSon(this);
    setParent(pParent);
}

void Agent::registerSon(Agent* pSon) {
    if (sonExists(pSon->getId())) {
        throw std::runtime_error("Agent with ID " + std::to_string(pSon->getId()) +
        " is already registered as son of agent with ID " + std::to_string(id) + ".");
    }
    sons[pSon->getId()] = pSon;
}

void Agent::unregisterAsSon() {
    if (!parent) {
        return;
    }
    parent->unregisterSon(id);
    parent = nullptr;
}

void Agent::unregisterSon(AgentId_t pSonId) {
    if (not sonExists(pSonId)) {
        // Throw an exception if the son is not agent's son
        throw std::runtime_error("Agent with ID " + std::to_string(pSonId) + " is not son of agent with ID " + std::to_string(id) + ".");
    }
    // Erase agent from son map
    sons.erase(pSonId);
}

Agent* Agent::getParent() {
    return parent;
}

void Agent::setParent(Agent* pPrent) {
    parent = pPrent;
}

AgentId_t Agent::getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t pSenderId, AgentId_t pControlled) {
    // Search among the agent's son
    std::queue<Agent*> queue;
    for (const auto &pair: sons) {
        Agent *son = pair.second;
        if (son->getId() == pSenderId || son->getId() == pControlled) {
            continue;
        }
        if (son->providedService(pServiceId)) {
            return son->getId();
        }
        queue.push(son);
    }

    // breadth-first search among agent's sons
    while (!queue.empty()) {
        Agent* controlledAgent = queue.front();
        queue.pop();
        for (const auto &pair: controlledAgent->getSons()) {
            Agent *son = pair.second;
            if (son->providedService(pServiceId)) {
                return son->getId();
            }
            queue.push(son);
        }
    } while (!queue.empty());

    return -1; // no agent provided the service in subhierarchy
}

bool Agent::sonExists(AgentId_t pSonId) {
    return sons.find(pSonId) != sons.end();
}

void Agent::initialization() {
    agentReasoning->initialization();
}

AgentReasoning* Agent::getReasoning() {
    return agentReasoning;
}

