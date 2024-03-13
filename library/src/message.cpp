#include "../include/message.h"

Message::Message(SimTime_t pExecTime, int pPriority, ServiceId_t pServiceId, AgentId_t pSdr, AgentId_t pRcvr);
    messageId = nextAgentId++;
    execTime = pExecTime;
    priority = pPriority;
    sender = pSdr;
    receiver = pRcvr;
    serviceId = pServiceId;
}