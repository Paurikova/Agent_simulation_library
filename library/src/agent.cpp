#include "../include/agent.h"

void Agent::process(ServiceId_t pServiceId, AgentId_t pSender) {
    // Find function connected with the entered service ID
    auto it = functionMap.find(pServiceId);
    if (it != functionMap.end()) {
        // Retrieve the function pointer and call it
        it->second(sender);
    } else {
        // Throw an exception if the function does not exist
        throw std::runtime_error("Function with service ID " + std::to_string(messageId) + " does not exist in the map.");
    }
}

int Agent::getCurrTime() {
    return currTime;
}

void Agent::sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pReceiver = -1, int pPriority = -1) {
    // Create a new message
    Message* newMessage = new Message{pTime, pPriority, pServiceId, getId(), receiver};
    // Add the new message to the message box
    outBox->push_back(newMessage);
}

void Agent::registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc) {
    // Add the function pointer to the function map
    functionMap[pServiceId] = pFunc;
}

void Agent::unregisterFunction(int pServiceId) {
    // Find the function pointer associated with the event ID
    auto it = functionMap.find(pServiceId);
    if (it != functionMap.end()) {
        // If the function pointer is found, remove it from the map
        functionMap.erase(it);
    } else {
        // If the function with the specified event ID does not exist, throw an exception
        throw std::runtime_error("Function with service ID " + std::to_string(pServiceId) + " does not exist in the map");
    }
}

Agent::Agent(Agent* pParent) {
    id = nextAgentId++;
    parent = pParent;
    currTime  = -1;
    outBox = std::make_unique<std::vector<Message*>>();
    schedule = std::make_unique<Schedule*>();
    // Register agent as child of his parent.
    pAgent->registerAsChild(pParent);
}

AgentId_t Agent::getId() {
    return id;
}

Message Agent::receiveMessage(Message pMsg) {
    // Add the received message to the agent's schedule
    schedule->pushMessage(pMsg);
}

void Agent::execute() {
    Message* message = schedule->popMessage(time); // Get the next scheduled message
    while (message) { // Loop until there are no more messages scheduled
        currTime = message->execTime; //Set the current time to the execution time of current message
        process(message->id, message->sender); // Process the message
        message = schedule->popMessage(); // Get the next scheduled message
    }
}

bool Agent::providedService(ServiceId_t pServiceId) {
    return functionMap.find(key) != functionMap.end();
}

Message* Agent::getTopOutboxMessage() {
    if (outBox->empty()) {
        return nullptr;
    }
    Message topMessage = outBox->back(); // Get the last message
    outBox->pop_back(); // Remove the last message
    return nullptr;
}

void Agent::registerAsChild(Agent* pParent) {
    // Call the parent's registerChild method to add the current agent to its list of children
    //Agent of simulation core doesn't have parent.
    if (pParent) {
        pParent->registerChild(this);
    }
    // Set the parent pointer of the current agent
    setParent(pParent);
}

void Agent::registerChild(Agent* pChild) {
    if (childExists(pChild)) {
        // Throw an exception if the child already exist
        throw std::runtime_error("Agent with ID " + std::to_string(pChild) +
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
    parent->unregisterChild(this);
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

Agent* Agent::setParent(Agent* pPrent) {
    parent = pPrent;
}

AgentId_t Agent::getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t sender) {
    if (providedService(pServiceId)) {
        return id;
    }

    // Search among the agent's child
    for (const auto& pair : childs) {
        Agent* child = pair.second;
        if (child->getId() == sender) {
            continue;
        }
        if (child->providedService(pServiceId)) {
            return child->getId();
        }
    }

    // Recursively search among the children of each agent
    for (const auto& pair : childs) {
        Agent* child = pair.second;
        if (child->getId() == sender) {
            continue;
        }
        AgentId_t id = child->getAgentIdProvidedService(pServiceId);
        if (id != -1) {
            return id;
        }
    }
    return -1;
}

bool childExists(AgentId_t pChildId) {
    return childs.find(pChildId) != childs.end();
}