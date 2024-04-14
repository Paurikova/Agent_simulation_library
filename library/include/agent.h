#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>

#include "types.h"
#include "schedule.h"
#include "petriNet.h"

/**
 * @brief Represents an agent in the simulation.
 *
 * Agents interact with each other by sending and receiving messages.
 */
class Agent {
private:
    AgentId_t id; /**< The unique identifier of the agent. */
    Agent* parent; /**< The pointer to agent's parent. */
    std::unordered_map<AgentId_t, Agent*> childs; /**< The map of pointers to agent's childs. */
    SimTime_t currTime; /**< The current time in the simulation. */
    std::unique_ptr<std::vector<Message*>> outBox ; /**< Outgoing message queue. */
    std::unordered_map<ServiceId_t, ExecFunct_t> functionMap; /**< Maps functions to service IDs. */
    PetriNet* petriNet; /**< Petri net for intelligent agent. */
    std::unique_ptr<Schedule> schedule ; /**< Schedule for managing agent's tasks. */
    AgentType agentType; /**< Type of agent. */

private:
    /**
     * @brief Processes an function.
     *
     * @param pServiceId The ID of the service.
     * @param pSender The ID of the sender.
     */
    void process(ServiceId_t pServiceId, AgentId_t pSender);

protected:
    /**
     * @brief Gets the current time in the simulation.
     *
     * @return The current time.
     */
    SimTime_t getCurrTime() const;

    /**
     * @brief Sends a message to another agent.
     *
     * @param pServiceId The ID of the service.
     * @param pReceiver The ID of the receiver agent.
     * @param pTime The time at which the message is sent.
     * @param pPriority The priority of the message (optional, default is -1).
     */
    void sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pReceiver = -1, int pPriority = -1);

    /**
     * @brief Registers a function to handle a specific service ID.
     *
     * @param pServiceId The ID of the service.
     * @param pFunc The function to be registered.
     */
    void registerFunction(ServiceId_t pServiceId, ExecFunct_t pFunc);

    /**
     * @brief Unregisters a function associated with a specific service ID.
     *
     * @param pServiceId The ID of the service.
     */
    void unregisterFunction(ServiceId_t pServiceId);

public:
    /**
     * @brief Constructs an Agent object.
     *
     * @param pParent The pointer to agent parent.
     */
    explicit Agent(AgentId_t pId, Agent* pParent);
    
    /**
     * @brief Set agent type.
     * @param newAgentType new agent type
     */
    void setAgentType(AgentType newAgentType);

    /**
     * @brief Gets the ID of the agent.
     *
     * @return The ID of the agent.
     */
    AgentId_t getId() const;

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
     * @brief Returns a pointer to the top message in the outbox.
     *
     * @return Pointer to the top message in the outbox.
     */
    Message* getTopOutboxMessage();

    /**
    * @brief Registers the agent as a child of the specified parent agent.
    *
    * @param pParent Pointer to the parent agent.
    */
    void registerAsChild(Agent* pParent);

    /**
     * @brief Registers the specified agent as a child of the current agent.
     *
     * @param pChild Pointer to the agent to be registered as a child.
     */
    void registerChild(Agent* pChild);

    /**
     * @brief Unregisters this agent as a child from its parent.
     */
    void unregisterAsChild();

    /**
     * @brief Unregisters a child agent with the specified ID.
     *
     * @param pChildId The ID of the child agent to unregister.
     */
    void unregisterChild(AgentId_t pChildId);

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
     * The service can provides current agent or some of his childs.
     *
     * @param pServiceId The ID of the service to check.
     * @param pSenderId The ID of the message sender.
     * @return The ID of the agent providing the service, or -1 if no agent provides the service.
     */
    AgentId_t getAgentIdProvidedService(ServiceId_t pServiceId, AgentId_t pSenderId);

    /**
     * @brief Checks if a child agent with the specified ID exists.
     *
     * @param pChildId The ID of the child agent to check.
     * @return True if a child agent with the specified ID exists, otherwise false.
     */
    bool childExists(AgentId_t pChildId);

    /**
     * @brief Agent initialization.
     *
     * Method registers all agent functions, etc.
     */
    void initialization(PetriNet* pPetriNet = nullptr);

    /**
     * @brief Function for registration of Petri Net.
     * @param registeredPetriNet    petri net
     */
    void registerPetriNet(PetriNet* pPetriNet);
    
    /**
    * @brief Registers functions for handling events.
    *
    * This method must be implemented by derived classes.
    */
    virtual void registerFunctions() = 0;
};