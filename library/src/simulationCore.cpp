#pragma once
#include "../include/simulationCore.h"

//ID = 1
//parent = nullptr
SimulationCore::SimulationCore(SimTime_t pStartTime, SimTime_t pEndTime) : Agent(nullptr) {
    currTime = pStartTime;
    endTime = pEndTime;
    registerAgent(this);
}

void SimulationCore::registerAgent(Agent* pParent) {
    if (!pParent or not agentExists(pParent)) {
        // If the parent is not entered, or parent hasn't existed yet
        throw std::runtime_error("Parent is not entered, or he hasn't registered yet.");
    }
    // Create new agent.
    Agent* agent = new Agent(pParent);
    // Register agent as child of his parent.
    agent->registerAsChild(pParent);
    // Registers an agent of simulation core based on his unique id
    agents[agent->getId()] = agent;
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

void SimulationCore::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int sender) {
        allDone(sender);
    });
}

void SimulationCore::registerAllFunctions() {
    // Iterate through all agents and register their functions
    for (auto& pair : agents) {
        pair.second->registerFunctions();
    }
}

void SimulationCore::initSimulation() {
    // Initialize the simulation by registering all functions for all agents
    registerAllFunctions();
}

void SimulationCore::performStep() {
    // Set to store IDs of agents that received messages
    std::unique_ptr<std::set<AgentId_t>> receivedAgentIds;
    // Get the next scheduled message
    Message* message = mainSchedule->popMessage(); // Get the next scheduled message
    currTime = message->execTime;
    // Loop until there are no more messages scheduled for the current time
    do {
        while (message) {
            // Check if the receiver agent exists
            if (not agentExists(message->receiver)) {
                throw std::runtime_error("No agent is registered under ID " + std::to_string(message.receiver) + ".");
            }
            // Insert the receiver ID into the set
            receivedAgentIds.insert(message->receiver);
            // Retrieve the receiver agent and deliver the message
            Agent *agent = agents[message.receiver];
            agent->receiveMessage(message);
            // Get the next scheduled message for the current time
            message = mainSchedule->popMessage(currTime);
        }

        // Execute agents that received messages and process their outbound messages
        for (AgentId_t id: receivedAgentIds) {
            Agent *agent = agents[id];
            agent->execute();
            receiveAgentMessages(agent)
        }

        // Get the next scheduled message for the current time
        message = mainSchedule->popMessage(currTime);
    } while (message);
}

void SimulationCore::receiveAgentMessages(Agent* agent) {
    // Retrieve the top message of the agent's outbox
    Message* message = agent->getTopMessage();
    // Process all messages of the agent's outbox
    while (message) {
        Agent* receiver;
        // If the receiver ID is not specified, find the closest agent that accepts the service
        if (message->receiver == -1) {
            Agent* sender = agents[message->sender];
            AgentId_t receiverId = -1;
            do {
                // Search for an agent ID providing the required service
                receiverId = sender->getAgentIdProvidedService(message->serviceId, sender->getId());
                sender = sender->getParent();
            } while (receiverId == -1 or sender == nullptr);

            if (receiverId == -1) {
                // If no agent provides the service, throw an error
                throw std::runtime_error("No service registered under ID " + std::to_string(message->serviceId) + ".");
            }
            // Assign the receiver ID to the message
            message->receiver = receiverId;
        }
        // Schedule the message for the receiver to the main schedule
        mainSchedule.pushMessage(message);
        // Get the next message of the agent
        message = agent->getTopMessage();
    }
}

bool SimulationCore::agentExists(AgentId_t pAgentId) {
    return agents.find(pAgentId) != agents.end();
}

//functions
void SimulationCore::allDone(int sender) {
    sendMessage(2,2,currTime+1,3);
    sendMessage(2,3,currTime,3);
}