#pragma once
#include "types.h"
#include "message.h"
#include <memory>
#include <unordered_map>
#include <variant>
#include <string>
#include <stdexcept>

/**
 * @brief Class for agent reasoning functionality.
 */
class AgentReasoning {
private:
    std::unique_ptr<std::vector<Message*>> outBox ; /**< Outgoing message queue. */
protected:
    /**
     * @brief Sends a message to another agent.
     *
     * @param pServiceId The ID of the service.
     * @param pTime The time at which the message is sent.
     * @param pSender The ID of the sender agent.
     * @param pReceiver The ID of the receiver agent.
     * @param pPriority The priority of the message (optional, default is -1).
     */
    void sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pSender, AgentId_t pReceiver = -1, int pPriority = -1, std::unordered_map<std::string, variant_t> pArgs = {});

public:
    /**
     * @brief Constructor for AgentReasoning class.
     */
    AgentReasoning();
    /**
     * @brief Retrieves the execution function associated with a service ID.
     *
     * @param pServiceId The service ID.
     * @param pSender    The sender ID.
     * @param pExecTime  The time of process execution.
     */
    virtual void process(ServiceId_t pServiceId, AgentId_t pSender, AgentId_t  pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) = 0;

    /**
    * @brief Checks if a service is provided.
    *
    * @param pServiceId The service ID to check.
    * @return True if the service is provided, false otherwise.
    */
    virtual bool providedService(ServiceId_t pServiceId) = 0;

    /**
     * @brief Returns a pointer to the top message in the outbox.
     *
     * @return Pointer to the top message in the outbox.
     */
    Message* getTopOutboxMessage();

    /**
     * @brief Pure virtual function for initialization.
     */
    virtual void initialization() = 0;

    /**
     * @brief Initial message. This function has empty implementation.
     * Initial message can send only simulation core.
     */
    virtual void initMessage();
};
