#include "customer.h"

//functions
void customer::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    int number = rand() % 2;
    // Should be new customer generated?
    if (number == 1) {
        // new customer is created
        //send him to shop
        sendMessage(1, pExecTime, pReceiver, 3);
    }
}

void customer::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        newCustomer(pSender, pReceiver, pExecTime);
    });
}