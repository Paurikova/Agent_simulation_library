//TODO incluce
#include "Manager1ReactiveReasoning.h"
void Manager1ReactiveReasoning::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    sendMessage(pServiceId, pExecTime, 1, pReceiver, 1);
}
void Manager1ReactiveReasoning::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Manager1ReactiveReasoning::startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Manager1ReactiveReasoning::initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Manager1ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        draw(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        startWindow(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        initialization(pSender, pReceiver, pExecTime, state);
    });
}