#pragma once
#include "types.h"

/**
 * @brief Definition of the Message structure.
 *
 * This structure represents a message that can be sent between agents.
 */
struct Message {
    static int nextMessageId;
    int messageId; /**< Unique identifier for the message */
    SimTime_t execTime; /**< Execution time of the message */
    int priority; /**< Priority of the message */
    AgentId_t sender; /**< ID of the sender agent */
    AgentId_t receiver; /**< ID of the receiver agent */
    ServiceId_t serviceId; /**< ID of the service */
    std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args; /**< Another args */

    /**
     * @brief Overloaded greater-than operator for comparing messages.
     *
     * This operator compares two messages based on their execution times and priorities.
     * If the execution times are equal, it compares their priorities.
     *
     * @param other The message to compare with.
     * @return true if the current message has a greater execution time or if the execution times are equal and the priority is higher; false otherwise.
     */
    bool operator<(const Message& other) const;

    /**
     * @brief Constructor for the Message structure.
     *
     * This constructor initializes a Message object with custom values.
     *
     * @param pExecTime The execution time of the message.
     * @param pPriority The priority of the message.
     * @param pSdr The ID of the sender agent.
     * @param pRcvr The ID of the receiver agent.
     * @param pArgs Another args of message */
    Message(SimTime_t pExecTime, int pPriority, ServiceId_t pServiceId, AgentId_t pSdr, AgentId_t pRcvr, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> pArgs);
};

// Define a custom comparison functor
struct MessagePtrComparator {
    bool operator()(const Message* m1, const Message* m2) const;
};