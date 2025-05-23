#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <memory>

#include "types_library.h"
#include "schedule.h"
#include "petriNetReasoning.h"
#include "agentReasoning.h"

/**
 * @brief Represents an agent in the simulation.
 *
 * Agents interact with each other by sending and receiving messages.
 */
class Agent {
private:
    AgentId_t id; /**< The unique identifier of the agent. */
    Agent* parent; /**< The pointer to agent's parent. */
    std::map<AgentId_t, Agent*> sons; /**< The map of pointers to agent's sons. */
    SimTime_t currTime; /**< The current time in the simulation. */
    std::unique_ptr<Schedule> schedule ; /**< Schedule for managing agent's tasks. */
protected:
    AgentReasoning* agentReasoning;
private:
    /**
     * @brief Processes an function.
     *
     * @param pServiceId The ID of the service.
     * @param pSender The ID of the sender.
     * * @param pSender The ID of the receiver.
     * @param pExecTime The time of execution.
     * @param state The additional parameters.
     */
    void process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime, State* state);

public:
    /**
     * @brief Constructs an Agent object.
     *
     * @param pId The ID of agent.
     * @param pParent The pointer to agent parent.
     * @param pAgentReasoning The reasoning of agent.
     */
    explicit Agent(AgentId_t pId, Agent* pParent, AgentReasoning* pAgentReasoning);

    /**
     * @brief Gets the ID of the agent.
     *
     * @return The ID of the agent.
     */
    AgentId_t getId() const;

    /**
     * @brief Get son of agent;
     * @return hash map of sons of agent
     */
    std::map<AgentId_t, Agent*> getSons();

    /**
     * @brief Receives a message and push it into agent's schedule.
     *
     * @param msg pMsg message to be received.
     */
    void receiveMessage(Message* pMsg);

    /**
     * @brief Execution of all actions for a schedule.
     */
    void execute();

    /**
     * @brief Bool if agent provides required service ID.
     *
     * @param pServiceId The ID of the service to be required.
     * @return True if the service is provided by agent, false otherwise.
     */
    bool providedService(ServiceId_t pServiceId);

    /**
     * @brief Returns a pointer to the top message in the outbox of agent reasoning.
     *
     * @return Pointer to the top message in the outbox.
     */
    Message* getTopOutboxMessage();

    /**
    * @brief Registers the agent as a son of the specified parent agent.
    *
    * @param pParent Pointer to the parent agent.
    */
    void registerAsSon(Agent* pParent);

    /**
     * @brief Registers the specified agent as a son of the current agent.
     *
     * @param pSon Pointer to the agent to be registered as a son.
     */
    void registerSon(Agent* pSon);

    /**
     * @brief Unregisters this agent as a son from its parent.
     */
    void unregisterAsSon();

    /**
     * @brief Unregisters a son agent with the specified ID.
     *
     * @param pSonId The ID of the son agent to unregister.
     */
    void unregisterSon(AgentId_t pSonId);

    /**
    * @brief Gets the pointer the agent's parent.
    *
    * @return The pointer to agent's parent.
    */
    Agent* getParent();

    /**
    * @brief Set the agent's parent.
    *
    * @param pPrent Pointer to new agent's parent.
    */
    void setParent(Agent* pPrent);

    /**
     * @brief Retrieves the ID of the agent providing the specified service.
     *
     * The service has to be provided by agent's son.
     *
     * @param pServiceId The ID of the service to check.
     * @param pSenderId The ID of the message sender.
     * @param pControlled The ID of agent controlled before.
     * @return The ID of the agent providing the service, or -1 if no agent provides the service.
     */
    AgentId_t getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t pSenderId, AgentId_t pControlled);

    /**
     * @brief Checks if a son agent with the specified ID exists.
     *
     * @param pSonId The ID of the son agent to check.
     * @return True if a son agent with the specified ID exists, otherwise false.
     */
    bool sonExists(AgentId_t pSonId);

    /**
     * @brief Agent initialization.
     *
     * Method provides initialization of agent reasoning.
     */
    virtual void initialization();

    /**
     * Get agent reasoning.
     * @return pointer to agent reasoning
     */
    AgentReasoning* getReasoning();
};