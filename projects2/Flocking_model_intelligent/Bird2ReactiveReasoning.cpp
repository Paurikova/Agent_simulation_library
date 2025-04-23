//TODO include
#include "Bird2ReactiveReasoning.h"
void Bird2ReactiveReasoning::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Bird2ReactiveReasoning::startMove(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Bird2ReactiveReasoning::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Bird2ReactiveReasoning::isNeighbout(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Bird2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        move(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        startMove(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        getPosition(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        isNeighbout(pSender, pReceiver, pExecTime, state);
    });
}