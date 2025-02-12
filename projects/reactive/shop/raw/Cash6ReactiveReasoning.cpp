//TODO incluce
#include "Cash6ReactiveReasoning.h"
void Cash6ReactiveReasoning::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Cash6ReactiveReasoning::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Cash6ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Cash6ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        endCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        processCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        acceptCustomer(pSender, pReceiver, pExecTime, state);
    });
}