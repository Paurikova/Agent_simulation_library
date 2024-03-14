#pragma once

#include <unordered_map>

#include "agent.h"
#include "message.h"
#include "const.h"

/**
 * @brief Represents the core of a simulation.
 *
 * This class manages the execution of the simulation and interaction
 * between different agents.
 */
class SimulationCore : Agent{
private:
    SimTime_t currTime; /**< Current simulation time. */
    SimTime_t endTime; /**< End time of the simulation. */
    std::unordered_map<AgentId_t, Agent*> agents; /**< Map of agent IDs to agent objects. */
    std::unique_ptr<Schedule*> mainSchedule; /**< Unique pointer to the main schedule. */

public:
    /**
     * @brief Constructs a new SimulationCore object.
     *
     * @param pStartTime The start time of the simulation.
     * @param pEndTime The end time of the simulation.
     */
    SimulationCore(SimTime_t pStartTime, SimTime_t pEndTime);

    /**
     * @brief Registers an agent with the simulation core.
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

private:
    /**
    * @brief Registers functions required by offered services.
    *
    * This function overrides the registerFunctions() method of the base class.
    * New function has to be added as lambda function.
    */
    void registerFunctions() override;

    /**
     * @brief Registers all functions registered by all agents.
     */
    void registerAllFunctions();

    /**
     * @brief Initializes the simulation.
     *
     * This function performs initialization tasks before starting the simulation.
     */
    void initSimulation();

    /**
     * @brief Performs a single step of the simulation.
     *
     * This function executes a single step of the simulation that consists from performing all messages of current time.
     */
    void performStep();

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

    //function
    void allDone(int sender);
};
