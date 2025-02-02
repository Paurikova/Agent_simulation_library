//TODO incluce
#include "agent3ReactiveReasoning.h"
void Agent3ReactiveReasoning::open(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}
void Agent3ReactiveReasoning::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}
void Agent3ReactiveReasoning::close(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}

void Agent3ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        open(pSender, pReceiver, pExecTime);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        removeCustomer(pSender, pReceiver, pExecTime);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        close(pSender, pReceiver, pExecTime);
    });
}