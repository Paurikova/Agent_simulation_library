#include "../include/agentReasoning.h"

AgentReasoning::AgentReasoning() {
    outBox = std::make_unique<std::vector<Message*>>();
}

void AgentReasoning::sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pSender, AgentId_t pReceiver, int pPriority) {
    // Create a new message
    Message* newMessage = new Message{pTime, pPriority, pServiceId, pSender, pReceiver};
    // Add the new message to the message box
    outBox->push_back(newMessage);
}

Message* AgentReasoning::getTopOutboxMessage() {
    if (outBox->empty()) {
        return nullptr;
    }
    Message* topMessage = outBox->back(); // Get the last message
    outBox->pop_back(); // Remove the last message
    return topMessage;
}