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
void Manager1ReactiveReasoning::closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Manager1ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Manager1ReactiveReasoning::generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Manager1ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        closeSimulation(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        acceptCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        generateCustomer(pSender, pReceiver, pExecTime, state);
    });
}