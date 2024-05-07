#include "../include/simCoreReactiveReasoning.h"
//functions
void SimCoreReactiveReasoning::allDone(int pSender, SimTime_t pExecTime) {
    sendMessage(2,pExecTime + 1, pSender,2, 3);
    sendMessage(2,pExecTime, pSender, 3,3);
}

void SimCoreReactiveReasoning::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        allDone(pSender, pExecTime);
    });
}