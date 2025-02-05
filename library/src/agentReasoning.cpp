#include "../include/agentReasoning.h"

void AgentReasoning::sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pSender, AgentId_t pReceiver, int pPriority, std::unordered_map<std::string, variant_t> args) {
    // Create a new message
    Message* newMessage = new Message{pTime, pPriority, pServiceId, pSender, pReceiver, args};
    // Add the new message to the message box
    outBox->push_back(newMessage);
}

AgentReasoning::AgentReasoning() {
    outBox = std::make_unique<std::vector<Message*>>();
}

Message* AgentReasoning::getTopOutboxMessage() {
    if (outBox->empty()) {
        return nullptr;
    }
    Message* topMessage = outBox->back(); // Get the last message
    outBox->pop_back(); // Remove the last message
    return topMessage;
}

void AgentReasoning::initMessage() {
    // this function is defined only for simulation core reasoning
}
