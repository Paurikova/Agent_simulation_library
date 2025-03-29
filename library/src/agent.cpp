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
    registerAsChild(pParent);
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

void Agent::registerAsChild(Agent* pParent) {
    if (!pParent) {
        return;
    }
    pParent->registerChild(this);
    setParent(pParent);
}

void Agent::registerChild(Agent* pChild) {
    if (childExists(pChild->getId())) {
        throw std::runtime_error("Agent with ID " + std::to_string(pChild->getId()) +
        " is already registered as child of agent with ID " + std::to_string(id) + ".");
    }
    sons[pChild->getId()] = pChild;
}

void Agent::unregisterAsChild() {
    if (!parent) {
        return;
    }
    parent->unregisterChild(id);
    parent = nullptr;
}

void Agent::unregisterChild(AgentId_t pChildId) {
    if (not childExists(pChildId)) {
        // Throw an exception if the child is not agent's child
        throw std::runtime_error("Agent with ID " + std::to_string(pChildId) + " is not child of agent with ID " + std::to_string(id) + ".");
    }
    // Erase agent from child map
    sons.erase(pChildId);
}

Agent* Agent::getParent() {
    return parent;
}

void Agent::setParent(Agent* pPrent) {
    parent = pPrent;
}

AgentId_t Agent::getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t pSenderId, AgentId_t pControlled) {
    // Search among the agent's child
    std::queue<Agent*> queue;
    for (const auto &pair: sons) {
        Agent *child = pair.second;
        if (child->getId() == pSenderId || child->getId() == pControlled) {
            continue;
        }
        if (child->providedService(pServiceId)) {
            return child->getId();
        }
        queue.push(child);
    }

    // breadth-first search among agent's sons
    while (!queue.empty()) {
        Agent* controlledAgent = queue.front();
        queue.pop();
        for (const auto &pair: controlledAgent->getSons()) {
            Agent *child = pair.second;
            if (child->providedService(pServiceId)) {
                return child->getId();
            }
            queue.push(child);
        }
    } while (!queue.empty());

    return -1; // no agent provided the service in subhierarchy
}

bool Agent::childExists(AgentId_t pChildId) {
    return sons.find(pChildId) != sons.end();
}

void Agent::initialization() {
    agentReasoning->initialization();
}

AgentReasoning* Agent::getReasoning() {
    return agentReasoning;
}

