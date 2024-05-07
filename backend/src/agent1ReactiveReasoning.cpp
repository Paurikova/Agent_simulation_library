
#include "../include/agent1ReactiveReasoning.h"
void Agent1ReactiveReasoning::writeHello(int pSender, SimTime_t pExecTime) {
    std::cout << "Hello." << std::endl;
}

void Agent1ReactiveReasoning::allDone(int pSender, SimTime_t pExecTime) {
    std::cout << "Done Agent1." << std::endl;
}

void Agent1ReactiveReasoning::registerFunctions() {
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        writeHello(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        allDone(pSender, pExecTime);
    });
}
