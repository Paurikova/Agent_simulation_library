#pragma once

#include <map>
#include <fstream>

#include "agent.h"
#include "agentManager.h"
#include "message.h"
#include "types_library.h"
#include "../../units/include/logger.h"

/**
 * @brief Represents the core of a simulation.
 *
 * This class manages the execution of the simulation and interaction
 * between different agents.
 */
class SimulationCore {
private:
    SimTime_t currTime; /**< Current simulation time. */
    std::map<AgentId_t, Agent*> agents; /**< Map of agent IDs to agent objects. */
    std::unique_ptr<Schedule> mainBox; /**< Unique pointer to the main schedule. */
    Logger* logger;
public:
    /**
     * @brief Constructs a new SimulationCore object.
     *
     * @param pAgentReasoning The reasoning of the agent.
     * @param pLogger Logging to console and creating log file.
     */
    SimulationCore(Logger* pLogger);

    /**
     * @brief Registers an agent with the simulation core.
     *
     * The registration of an agent as a parent-child is done when the agent is created.
     * Do agent initialization (functions registration etc.)
     *
     * @param pAgent Pointer to the agent to be registered.
     */
    void registerAgent(Agent* pAgent);

    /**
     * @brief Unregisters an agent from the simulation core.
     *
     * @param pAgentId The ID of the agent to be unregistered.
     */
    void unregisterAgent(AgentId_t pAgentId);

    /**
     * @brief Runs the simulation.
     *
     * This function executes the simulation until the end time is reached.
     *
     * @param pNumberOfRepl Number of replications.
     * @param pLengthOfRepl Length of one replication.
     */
    void runSimulation(int pNumberOfRepl, int pLengthOfRepl);

    /**
     * @brief Push messsage to simulation core schedule.
     * @param pMessage Pushed message.
     */
    void pushToMainBox(Message* pMessage);

    /**
     * @brief Get size of agent's array.
     * @return Size
     */
    int getAgentsSize();

    /**
     * Get agent at position in array;
     * @param pos position of agent in array
     * @return pointer to agent
     */
    Agent* getAgent(int pos);

    /**
    * @brief Receives messages from agents.
    *
    * This function receives messages from all registered agents and processes them.
    *
    * @param agent Pointer to the agent from which messages are received.
    */
    void receiveAgentMessages(Agent* pAgent);

    /**
     * @brief Initializes the simulation.
     *
     * This function performs initialization tasks before starting the simulation.
     */
    void initialization();

private:
    /**
     * @brief Checks if an agent with the specified ID exists in the simulation core.
     *
     * @param pAgentId The ID of the agent to check for existence.
     * @return true if an agent with the specified ID exists, false otherwise.
     */
    bool agentExists(AgentId_t pAgentId);

    /**
     * @brief Adds a receiver for the message.
     *
     * @param pMessage Pointer to the message being received.
     */
    void addReceiver(Message* pMessage);
};
