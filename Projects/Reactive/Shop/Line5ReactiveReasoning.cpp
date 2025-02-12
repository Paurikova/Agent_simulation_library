//TODO incluce
#include "Line5ReactiveReasoning.h"
void Line5ReactiveReasoning::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Line5ReactiveReasoning::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Line5ReactiveReasoning::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Line5ReactiveReasoning::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Line5ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        hasCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeFromShop(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        addToLine(pSender, pReceiver, pExecTime, state);
    });
}