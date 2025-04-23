//TODO include
#include "Customer4ReactiveReasoning.h"
void Customer4ReactiveReasoning::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Customer4ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        createCustomer(pSender, pReceiver, pExecTime, state);
    });
}