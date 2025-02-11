#pragma once

#include <unordered_map>
#include <fstream>

#include "agent.h"
#include "message.h"
#include "types_library.h"
#include "../../units/include/logger.h"

/**
 * @brief Represents the core of a simulation.
 *
 * This class manages the execution of the simulation and interaction
 * between different agents.
 */
class SimulationCore : public Agent{
private:
    SimTime_t currTime; /**< Current simulation time. */
    std::unordered_map<AgentId_t, Agent*> agents; /**< Map of agent IDs to agent objects. */
    std::unique_ptr<Schedule> mainSchedule; /**< Unique pointer to the main schedule. */
    Logger* logger;
public:
    /**
     * @brief Constructs a new SimulationCore object.
     *
     * @param pAgentReasoning The reasoning of the agent.
     * @param pLogger Logging to console and creating log file.
     */
    SimulationCore(AgentReasoning* pAgentReasoning, Logger* pLogger);

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
    void unregisterAgent(int pAgentId);

    /**
     * @brief Runs the simulation.
     *
     * This function executes the simulation until the end time is reached.
     */
    void runSimulation();

    /**
     * @brief Push messsage to simulation core schedule.
     * @param pMessage Pushed message.
     */
    void pushToMainSchedule(Message* pMessage);

private:
    /**
     * @brief Initializes the simulation.
     *
     * This function performs initialization tasks before starting the simulation.
     */
    void initSimulation();

    /**
    * @brief Receives messages from agents.
    *
    * This function receives messages from all registered agents and processes them.
    *
    * @param agent Pointer to the agent from which messages are received.
    */
    void receiveAgentMessages(Agent* agent);

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
