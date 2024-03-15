#include <set>
#include "../include/simulationCore.h"

//ID = 1
//parent = nullptr
SimulationCore::SimulationCore(SimTime_t pStartTime, SimTime_t pEndTime) : Agent(nullptr) {
    currTime = pStartTime;
    endTime = pEndTime;
    registerAgent(this);
    mainSchedule = std::make_unique<Schedule>();
}

void SimulationCore::registerAgent(Agent* pAgent) {
    //Note: The registration of an agent as a parent-child is done when the agent is created.
    if (!pAgent) {
        throw std::runtime_error("Cannot register agent because the agent is nullptr.");
    }
    // Registers an agent of simulation core based on his unique id
    agents[pAgent->getId()] = pAgent;
    // Make agent initialization
    pAgent->initialization();
}

void SimulationCore::unregisterAgent(int agentId) {
    // Find the agent with the specified ID in the map
    if (not agentExists(agentId)) {
        // If the agent is not found, throw an exception
        throw std::runtime_error("Agent with event ID " + std::to_string(agentId) + " does not exist in the map");
    }
    // Unregister agent as child of other agent.
    agents[agentId]->unregisterAsChild();
    // Unregister agent from simulation core.
    agents.erase(agentId);
}

void SimulationCore::runSimulation() {
    // Initialization
    initSimulation();
    //Run
    while (currTime < endTime) {
        performStep();
    }
}

void SimulationCore::pushToMainSchedule(Message* pMessage) {
    if (!pMessage) {
        throw std::runtime_error("The received message is nullptr.");
    }
    // Add receiver of message if he is missing
    if (pMessage->receiver == -1) {
        addReceiver(pMessage);
    }
    // Push message to simulation core schedule.
    mainSchedule->pushMessage(pMessage);
}

void SimulationCore::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int sender) {
        allDone(sender);
    });
}

void SimulationCore::initSimulation() {
    // empty
}

void SimulationCore::performStep() {
    // Set to store IDs of agents that received messages
    std::unique_ptr<std::set<AgentId_t>> receivedAgentIds = std::make_unique<std::set<AgentId_t>>();
    // Get the next scheduled message
    Message* message = mainSchedule->popMessage(); // Get the next scheduled message
    // Loop until there are no more messages scheduled for the current time
    while (message) {
        currTime = message->execTime;
        while (message) {
            // Check if the receiver agent exists
            if (not agentExists(message->receiver)) {
                throw std::runtime_error("No agent is registered under ID " + std::to_string(message->receiver) + ".");
            }
            // Insert the receiver ID into the set
            receivedAgentIds->insert(message->receiver);
            // Retrieve the receiver agent and deliver the message
            Agent *agent = agents[message->receiver];
            agent->receiveMessage(message);
            // Get the next scheduled message for the current time
            message = mainSchedule->popMessage(currTime);
        }

        // Execute agents that received messages and process their outbound messages
        for (AgentId_t id: *receivedAgentIds) {
            Agent *agent = agents[id];
            agent->execute();
            receiveAgentMessages(agent);
        }
        // Clean the set.
        receivedAgentIds->clear();

        // Get the next scheduled message
        message = mainSchedule->popMessage();
    }
}

void SimulationCore::receiveAgentMessages(Agent* agent) {
    // Retrieve the top message of the agent's outbox
    Message* message = agent->getTopOutboxMessage();
    // Process all messages of the agent's outbox
    while (message) {
        Agent* receiver;
        // If the receiver ID is not specified, find the closest agent that accepts the service
        if (message->receiver == -1) {
            addReceiver(message);
        }
        // Schedule the message for the receiver to the main schedule
        mainSchedule->pushMessage(message);
        // Get the next message of the agent
        message = agent->getTopOutboxMessage();
    }
}

bool SimulationCore::agentExists(AgentId_t pAgentId) {
    return agents.find(pAgentId) != agents.end();
}

void SimulationCore::addReceiver(Message* pMessage) {
    Agent* sender = agents[pMessage->sender];
    AgentId_t receiverId = -1;
    do {
        // Search for an agent ID providing the required service
        receiverId = sender->getAgentIdProvidedService(pMessage->serviceId, sender->getId());
        sender = sender->getParent();
    } while (receiverId == -1 or sender != nullptr);

    if (receiverId == -1) {
        // If no agent provides the service, throw an error
        throw std::runtime_error("No service registered under ID " + std::to_string(pMessage->serviceId) + ".");
    }
    // Assign the receiver ID to the message
    pMessage->receiver = receiverId;
}

//functions
void SimulationCore::allDone(int sender) {
    sendMessage(2,currTime+1,2, 3);
    sendMessage(2,currTime, 3,3);
}