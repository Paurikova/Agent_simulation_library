#include "customer.h"

//functions
void Customer::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    int isCreated = rand() % 2;
    // Should be new customer created?
    if (isCreated == 1) {
        nCustomers += 1;
        // new customer is created
        //send him to shop
        sendMessage(2, pExecTime, pReceiver, pSender);
    }
}

void Customer::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        createCustomer(pSender, pReceiver, pExecTime);
    });
}