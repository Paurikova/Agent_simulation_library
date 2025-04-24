//TODO include
#include "Line5ReactiveReasoning.h"
void Line5ReactiveReasoning::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Line5ReactiveReasoning::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Line5ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        addToLine(pSender, pReceiver, pExecTime, state);
    });
}