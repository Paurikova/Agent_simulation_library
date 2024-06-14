#include "agent1ReactiveReasoning.h"
void Agent1ReactiveReasoning::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    sendMessage(pServiceId, pExecTime, 1, pReceiver, 1);
}
void Agent1ReactiveReasoning::Name(int pSender, SimTime_t pExecTime) {
    //add your code
}
void Agent1ReactiveReasoning::registerFunctions() {
    //functions
    registerFunction(7, [this](int pSender, SimTime_t pExecTime) {
        Name(pSender, pExecTime);
    });
    //registration
}