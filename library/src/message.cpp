#include "../include/message.h"

int Message::nextMessageId = 1;

bool Message::operator<(const Message& other) const {
    return execTime == other.execTime ? priority < other.priority : execTime > other.execTime;
}

Message::Message(SimTime_t pExecTime, int pPriority, ServiceId_t pServiceId, AgentId_t pSdr, AgentId_t pRcvr) {
    messageId = nextMessageId++;
    execTime = pExecTime;
    priority = pPriority;
    sender = pSdr;
    receiver = pRcvr;
    serviceId = pServiceId;
}
