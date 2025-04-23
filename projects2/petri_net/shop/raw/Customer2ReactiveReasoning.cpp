//TODO include
#include "Customer2ReactiveReasoning.h"
void Customer2ReactiveReasoning::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Customer2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        createCustomer(pSender, pReceiver, pExecTime, state);
    });
}