#pragma once
#include "agent.h"
#include "message.h"
#include "types_library.h"
#include "../../units/include/logger.h"
#include "simulationCore.h"

/**
 * @brief Main agent responsible for managing communication between agents.
 */
class AgentManager : public Agent {
    std::unique_ptr<SimulationCore> simCore;
public:
    /**
     * @brief Constructs an AgentManager with the given reasoning module and logger.
     *
     * @param pAgentReasoning Pointer to the AgentReasoning module.
     * @param pLogger Pointer to the Logger instance for logging simulation events.
     */
    AgentManager(AgentReasoning* pAgentReasoning, Logger* pLogger);

    /**
     * @brief Initializes the simulation environment.
     *
     * This method prepares necessary components before executing the simulation.
     */
    void initSimulation();

    /**
     * @brief Runs the simulation for a specified number of replications and duration.
     *
     * @param numberOfReplications The number of times the simulation should be repeated.
     * @param lengthOfReplication The duration of each simulation replication.
     */
    void runSimulation(int numberOfReplications, int lengthOfReplication);

    /**
     * @brief Registers a new agent in the system.
     *
     * @param pAgent Pointer to the Agent to be registered.
     */
    void registerAgent(Agent* pAgent);

    /**
     * @brief Unregisters an agent from the system using its unique identifier.
     *
     * @param agentId The ID of the agent to be removed.
     */
    void unregisterAgent(int agentId);

    /**
    * @brief Retrieves the number of registered agents.
    *
    * @return The number of agents currently managed.
    */
    int getAgentsSize();

    /**
     * @brief Retrieves an agent by its position in the internal storage.
     *
     * @param position The index of the agent in the internal data structure.
     * @return Pointer to the retrieved Agent.
     */
    Agent* getAgent(int position);
};