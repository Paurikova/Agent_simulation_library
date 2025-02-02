//TODO incluce
#include "agent2ReactiveReasoning.h"
void Agent2ReactiveReasoning::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}

void Agent2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        createCustomer(pSender, pReceiver, pExecTime);
    });
}