//TODO include
#include "Shop3ReactiveReasoning.h"
void Shop3ReactiveReasoning::addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Shop3ReactiveReasoning::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Shop3ReactiveReasoning::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Shop3ReactiveReasoning::close(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}
void Shop3ReactiveReasoning::open(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
}

void Shop3ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        addCustomerToLine(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        newCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        close(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        open(pSender, pReceiver, pExecTime, state);
    });
}