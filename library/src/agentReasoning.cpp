#include "../include/agentReasoning.h"

void AgentReasoning::sendMessage(ServiceId_t pServiceId, SimTime_t pTime, AgentId_t pSender, AgentId_t pReceiver, int pPriority, State* state) {
    Message* newMessage = new Message{pTime, pPriority, pServiceId, pSender, pReceiver, state};
    outBox->push_back(newMessage);
}

AgentReasoning::AgentReasoning(Logger* pLogger) {
    logger = pLogger;
    outBox = std::make_unique<std::vector<Message*>>();
}

Message* AgentReasoning::getTopOutboxMessage() {
    if (outBox->empty()) {
        return nullptr;
    }
    Message* topMessage = outBox->back();
    outBox->pop_back(); // Remove the last message
    return topMessage;
}

void AgentReasoning::initialization() {
    Message* msg = outBox->back();
    while (msg) {
        outBox->pop_back();
        delete msg;
        msg = outBox->back();
    }
}

void AgentReasoning::initMessage() {
    // this function is defined only for simulation core reasoning
}
