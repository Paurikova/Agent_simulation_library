//TODO include
#include "Bird2ReactiveReasoning.h"
void Bird2ReactiveReasoning::setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Bird2ReactiveReasoning::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Bird2ReactiveReasoning::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Bird2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        setPosition(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        move(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        getPosition(pSender, pReceiver, pExecTime, state);
    });
}