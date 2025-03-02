#include <set>
#include "../include/simulationCore.h"

//ID = 1
//parent = nullptr
SimulationCore::SimulationCore(Logger* pLogger) : logger(pLogger) {
    currTime = -1;
    mainSchedule = std::make_unique<Schedule>();
}

void SimulationCore::registerAgent(Agent* pAgent) {
    //Note: The registration of an agent as a parent-child is done when the agent is created.
    if (!pAgent) {
        throw std::runtime_error("Cannot register agent because the agent is nullptr.");
    }
    if (pAgent->getId() != SIMULATION_CORE_ID && !pAgent->getParent()) {
        throw std::runtime_error("Cannot register agent because the agent's parent is nullptr.");
    }
    agents[pAgent->getId()] = pAgent;
}

void SimulationCore::unregisterAgent(int agentId) {
    if (not agentExists(agentId)) {
        throw std::runtime_error("Agent with event ID " + std::to_string(agentId) + " does not exist in the map");
    }
    agents[agentId]->unregisterAsChild();
    agents.erase(agentId);
}

void SimulationCore::runSimulation(int pNumberOfRepl, int pLengthOfRepl) {
    for (int i = 0; i < pNumberOfRepl; i++) {
        initialization();
        //Run
        // Set to store IDs of agents that received messages
        std::unique_ptr<std::set<AgentId_t>> receivedAgentIds = std::make_unique<std::set<AgentId_t>>();
        // Get the next scheduled message
        Message *message = mainSchedule->popMessage();
        // Loop until there are no more messages scheduled for the current time
        int last_exec_time = -1;
        while (message) {
            if (message->execTime > last_exec_time) {
                logger->log(fmt::format("Exec time: {}\n", message->execTime));
                last_exec_time = message->execTime;
            }
            currTime = message->execTime;
            if (pLengthOfRepl > 0 && currTime > pLengthOfRepl) {
                break;
            }
            while (message) {
                if (not agentExists(message->receiver)) {
                    throw std::runtime_error("No agent is registered under ID " + std::to_string(message->receiver) + ".");
                }
                receivedAgentIds->insert(message->receiver);
                // Retrieve the receiver agent and deliver the message
                Agent *agent = agents[message->receiver];
                agent->receiveMessage(message);
                message = mainSchedule->popMessage(currTime);
            }

            // Execute agents that received messages and process their outbound messages
            for (AgentId_t id: *receivedAgentIds) {
                Agent *agent = agents[id];
                agent->execute();
                receiveAgentMessages(agent);
            }
            receivedAgentIds->clear();

            message = mainSchedule->popMessage();
        }
    }
}

void SimulationCore::pushToMainSchedule(Message* pMessage) {
    if (!pMessage) {
        throw std::runtime_error("The received message is nullptr.");
    }
    if (pMessage->receiver == -1) {
        addReceiver(pMessage);
    }
    mainSchedule->pushMessage(pMessage);
}

int SimulationCore::getAgentsSize() {
    return agents.size();
}

Agent* SimulationCore::getAgent(int pos) {
    if (pos < 0 || pos >= agents.size()) {
        return nullptr;
    }
    return agents[pos];
}

void SimulationCore::initialization() {
    Message* msg = mainSchedule->popMessage();
    while (msg) {
        delete msg;
        msg = mainSchedule->popMessage();
    }
    for (auto& [id, agent] : agents) {
        agent->initialization();
    }
}

void SimulationCore::receiveAgentMessages(Agent* agent) {
    Message* message = agent->getTopOutboxMessage();
    // Process all messages of the agent's outbox
    while (message) {
        Agent* receiver;
        // If the receiver ID is not specified, find the closest agent that accepts the service
        if (message->receiver == -1) {
            addReceiver(message);
        }
        mainSchedule->pushMessage(message);
        message = agent->getTopOutboxMessage();
    }
}

bool SimulationCore::agentExists(AgentId_t pAgentId) {
    return agents.find(pAgentId) != agents.end();
}

void SimulationCore::addReceiver(Message* pMessage) {
    Agent* sender = agents[pMessage->sender];
    AgentId_t receiverId = -1;
    AgentId_t controlled = -1;

    // Create a set to track visited agents
    std::unordered_set<AgentId_t> visitedAgents;

    do {
        // Check if the sender has already been visited (detect loop)
        if (visitedAgents.find(sender->getId()) != visitedAgents.end()) {
            throw std::runtime_error("Detected a loop in the agent hierarchy.");
        }

        // Add the current sender to the visited set
        visitedAgents.insert(sender->getId());

        // Search for an agent ID providing the required service
        receiverId = sender->getAgentIdProvidedService(pMessage->serviceId, sender->getId(), controlled);
        controlled = sender->getId();
        sender = sender->getParent();
        if (sender == nullptr)
            break;
    } while (receiverId == -1);

    if (receiverId == -1) {
        throw std::runtime_error("No service registered under ID " + std::to_string(pMessage->serviceId) + ".");
    }
    pMessage->receiver = receiverId;
}