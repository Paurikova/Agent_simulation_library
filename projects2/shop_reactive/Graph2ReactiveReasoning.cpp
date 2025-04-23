//TODO include
#include "Graph2ReactiveReasoning.h"
void Graph2ReactiveReasoning::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Graph2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        draw(pSender, pReceiver, pExecTime, state);
    });
}