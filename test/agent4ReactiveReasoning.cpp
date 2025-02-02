//TODO incluce
#include "agent4ReactiveReasoning.h"
void Agent4ReactiveReasoning::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}
void Agent4ReactiveReasoning::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}
void Agent4ReactiveReasoning::NremoveFromLine(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}
void Agent4ReactiveReasoning::addToLine(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}

void Agent4ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        hasCustomer(pSender, pReceiver, pExecTime);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        removeFromShop(pSender, pReceiver, pExecTime);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        NremoveFromLine(pSender, pReceiver, pExecTime);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        addToLine(pSender, pReceiver, pExecTime);
    });
}