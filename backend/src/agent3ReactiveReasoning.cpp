#include "../include/agent3ReactiveReasoning.h"

//functions
void Agent3ReactiveReasoning::writeGoodbye(int pSender, SimTime_t pExecTime) {
    std::cout << "Goodbye." << std::endl;
    sendMessage(1,pExecTime, pSender, 1);
}

void Agent3ReactiveReasoning::allDone(int pSender, SimTime_t pExecTime) {
    std::cout << "Done Agent3." << std::endl;
}

void Agent3ReactiveReasoning::registerFunctions() {
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        writeGoodbye(pSender, pExecTime);
    });
    registerFunction(3, [this](int pSender, SimTime_t pExecTime) {
        allDone(pSender, pExecTime);
    });
}