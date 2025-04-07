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
public:
    /**
     * @brief Constructs an AgentManager with the given reasoning module and logger.
     *
     * @param pAgentReasoning Pointer to the AgentReasoning module.
     * @param pLogger Pointer to the Logger instance for logging simulation events.
     */
    AgentManager(AgentReasoning* pAgentReasoning, Logger* pLogger);

    /**
     * @brief Initializes the agent with the init messages.
     *
     * This method prepares necessary components before executing the simulation.
     */
    void initialization() override;
};