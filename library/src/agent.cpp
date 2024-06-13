#include "../include/agent.h"

void Agent::process(ServiceId_t pServiceId, AgentId_t pSender, SimTime_t execTime) {
    agentReasoning->process(pServiceId, pSender, execTime);
}

Agent::Agent(AgentId_t pId, Agent* pParent, AgentReasoning* pAgentReasoning) {
    id = pId;
    parent = pParent;
    currTime  = -1;
    schedule = std::make_unique<Schedule>();
    if (pAgentReasoning == nullptr) {
        // Throw an exception that agent type is invalid.
        throw std::runtime_error(
                "Agent type is invalid.");
    }
    agentReasoning = pAgentReasoning;
    // Register agent as child of his parent.
    registerAsChild(pParent);
}

AgentId_t Agent::getId() const {
    return id;
}

void Agent::receiveMessage(Message* pMsg) {
    // Add the received message to the agent's schedule
    schedule->pushMessage(pMsg);
}

void Agent::execute() {
    Message* message = schedule->popMessage(); // Get the next scheduled message
    while (message) { // Loop until there are no more messages scheduled
        currTime = message->execTime; //Set the current time to the execution time of current message
        process(message->serviceId, message->sender, message->execTime); // Process the message
        message = schedule->popMessage(); // Get the next scheduled message
    }
}

bool Agent::providedService(ServiceId_t pServiceId) {
    return agentReasoning->providedService(pServiceId);
}

Message* Agent::getTopOutboxMessage() {
    return agentReasoning->getTopOutboxMessage();
}

void Agent::registerAsChild(Agent* pParent) {
    // Call the parent's registerChild method to add the current agent to its list of children
    //Agent of simulation core doesn't have parent.
    if (!pParent) {
        return;
    }
    pParent->registerChild(this);
    // Set the parent pointer of the current agent
    setParent(pParent);
}

void Agent::registerChild(Agent* pChild) {
    if (childExists(pChild->getId())) {
        // Throw an exception if the child already exist
        throw std::runtime_error("Agent with ID " + std::to_string(pChild->getId()) +
        " is already registered as child of agent with ID " + std::to_string(id) + ".");
    }
    childs[pChild->getId()] = pChild;
}

void Agent::unregisterAsChild() {
    // Simulation core agent doesn't have parent
    if (!parent) {
        return;
    }
    // Unregister agent from parent child's map.
    parent->unregisterChild(id);
    // Set agent's parent to nullptr.
    parent = nullptr;
}

void Agent::unregisterChild(AgentId_t pChildId) {
    if (not childExists(pChildId)) {
        // Throw an exception if the child is not agent's child
        throw std::runtime_error("Agent with ID " + std::to_string(pChildId) + " is not child of agent with ID " + std::to_string(id) + ".");
    }
    // Erase agent from child map
    childs.erase(pChildId);
}

Agent* Agent::getParent() {
    return parent;
}

void Agent::setParent(Agent* pPrent) {
    parent = pPrent;
}

AgentId_t Agent::getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t pSenderId, AgentId_t pControlled) {
    // Search among the agent's child
    for (const auto& pair : childs) {
        Agent* child = pair.second;
        if (child->getId() == pSenderId || child->getId() == pControlled) {
            continue;
        }
        if (child->providedService(pServiceId)) {
            return child->getId();
        }
    }

    // Recursively search among the children of each agent
    for (const auto& pair : childs) {
        Agent* child = pair.second;
        if (child->getId() == pSenderId || child->getId() == pControlled) {
            continue;
        }
        AgentId_t id = child->getAgentIdProvidedService(pServiceId, pSenderId, pControlled);
        if (id != -1) {
            return id;
        }
    }
    return -1;
}

bool Agent::childExists(AgentId_t pChildId) {
    return childs.find(pChildId) != childs.end();
}

void Agent::initialization() {
    // Call all necessary functions for agent initialization
    agentReasoning->initialization();
}

