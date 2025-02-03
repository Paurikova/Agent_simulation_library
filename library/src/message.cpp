#include <utility>

#include "../include/message.h"

int Message::nextMessageId = 1;

bool Message::operator<(const Message& other) const {
    return execTime == other.execTime ? priority < other.priority : execTime > other.execTime;
}

Message::Message(SimTime_t pExecTime, int pPriority, ServiceId_t pServiceId, AgentId_t pSdr, AgentId_t pRcvr, std::unordered_map<std::string, std::variant<int, double, std::string>> pArgs) {
    messageId = nextMessageId++;
    execTime = pExecTime;
    priority = pPriority;
    sender = pSdr;
    receiver = pRcvr;
    serviceId = pServiceId;
    args = std::move(pArgs);
}

bool MessagePtrComparator::operator()(const Message* m1, const Message* m2) const {
    //Message m1 has a priority lower than that of message m2 if its execution time is less than that of m2.
    // If the execution times are equal, then the priority is determined by the message with the lower priority number.
    return *m1 < *m2;
}
