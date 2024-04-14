#include "../include/agent.h"

void Agent::process(ServiceId_t pServiceId, AgentId_t pSender) {
    if (agentType == AgentType::REACTIVE) {
        // Find function connected with the entered service ID
        auto it = functionMap.find(pServiceId);
        if (it != functionMap.end()) {
            // Retrieve the function pointer and call it
            it->second(pSender);
        } else {
            // Throw an exception if the function does not exist
            throw std::runtime_error(
                    "Function with service ID " + std::to_string(pServiceId) + " does not exist in the map.");
        }
    } else if (agentType == AgentType::INTELLIGENT) {
        ExecFunct_t funct = petriNet->getExecFunct(pServiceId);
        funct(pSender);
    } else {
        // Throw an exception that agent type is invalid.
        throw std::runtime_error(
                "Agent type is invalid.");
    }
}

SimTime_t Agent::getCurrTime() const {
    return currTime;
}

void Agent::sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pReceiver, int pPriority) {
    // Create a new message
    auto newMessage = new Message{pTime, pPriority, pServiceId, getId(), pReceiver};
    // Add the new message to the message box
    outBox->push_back(newMessage);
}

void Agent::registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc) {
    // Add the function pointer to the function map
    functionMap[pServiceId] = std::move(pFunc);
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

Agent::Agent(AgentId_t pId, Agent* pParent) {
    id = pId;
    parent = pParent;
    currTime  = -1;
    outBox = std::make_unique<std::vector<Message*>>();
    schedule = std::make_unique<Schedule>();
    // Register agent as child of his parent.
    registerAsChild(pParent);
    agentType = AgentType::REACTIVE;
    petriNet = nullptr;
}

void Agent::setAgentType(AgentType newAgentType) {
    agentType = newAgentType;
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
        process(message->serviceId, message->sender); // Process the message
        message = schedule->popMessage(); // Get the next scheduled message
    }
}

bool Agent::providedService(ServiceId_t pServiceId) {
    if (agentType == AgentType::REACTIVE)
        return functionMap.find(pServiceId) != functionMap.end();
    else if (agentType == AgentType::INTELLIGENT)
        return petriNet->providedService(pServiceId);
}

Message* Agent::getTopOutboxMessage() {
    if (outBox->empty()) {
        return nullptr;
    }
    Message* topMessage = outBox->back(); // Get the last message
    outBox->pop_back(); // Remove the last message
    return topMessage;
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

AgentId_t Agent::getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t pSenderId) {
    if (providedService(pServiceId)) {
        return id;
    }

    // Search among the agent's child
    for (const auto& pair : childs) {
        Agent* child = pair.second;
        if (child->getId() == pSenderId) {
            continue;
        }
        if (child->providedService(pServiceId)) {
            return child->getId();
        }
    }

    // Recursively search among the children of each agent
    for (const auto& pair : childs) {
        Agent* child = pair.second;
        if (child->getId() == pSenderId) {
            continue;
        }
        AgentId_t id = child->getAgentIdProvidedService(pServiceId, pSenderId);
        if (id != -1) {
            return id;
        }
    }
    return -1;
}

bool Agent::childExists(AgentId_t pChildId) {
    return childs.find(pChildId) != childs.end();
}

void Agent::initialization(PetriNet* pPetriNet) {
    // Call all necessary functions for agent initialization
    registerFunctions();
    registerPetriNet(pPetriNet);
}

void Agent::registerPetriNet(PetriNet* pPetriNet) {
    petriNet = pPetriNet;
}