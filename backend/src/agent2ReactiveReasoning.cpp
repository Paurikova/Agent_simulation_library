#include "../include/agent2ReactiveReasoning.h"

//functions
void Agent2ReactiveReasoning::writeGoodbye(int pSender, SimTime_t pExecTime) {
    std::cout << "Goodbye." << std::endl;
    sendMessage(1,pExecTime, pSender, 1);
}

void Agent2ReactiveReasoning::allDone(int pSender, SimTime_t pExecTime) {
    std::cout << "Done Agent2." << std::endl;
}

void Agent2ReactiveReasoning::registerFunctions() {
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        writeGoodbye(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        allDone(pSender, pExecTime);
    });
}