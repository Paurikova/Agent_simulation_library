//TODO incluce
#include "agent5ReactiveReasoning.h"
void Agent5ReactiveReasoning::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}
void Agent5ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    //add your code
}

void Agent5ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        processCustomer(pSender, pReceiver, pExecTime);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        acceptCustomer(pSender, pReceiver, pExecTime);
    });
}