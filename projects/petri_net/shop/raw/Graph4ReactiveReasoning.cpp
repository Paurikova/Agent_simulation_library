//TODO incluce
#include "Graph4ReactiveReasoning.h"
void Graph4ReactiveReasoning::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Graph4ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        draw(pSender, pReceiver, pExecTime, state);
    });
}