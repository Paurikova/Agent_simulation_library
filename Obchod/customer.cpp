#include "customer.h"

//functions
void customer::checkNewCustomer(int pSender, SimTime_t pExecTime) {
    int number = rand() % 2;
    // Should be new customer generated?
    if (number == 1) {
        // new customer is created
        //send him to shop
        sendMessage(1, pExecTime, 2, 3);
    }
}

void customer::registerFunctions() {
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        checkNewCustomer(pSender, pExecTime);
    });
}