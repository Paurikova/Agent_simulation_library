#include "customer.h"

//functions
void Customer::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: createCustomer", pReceiver));
    int isCreated = rand() % 2;
    // Should be new customer created?
    if (isCreated == 1) {
        nCustomers += 1;
        logger->log(fmt::format("  [{}]\n", nCustomers));
        // new customer is created
        //send him to shop
        sendMessage(2, pExecTime, pReceiver, pSender);
    } else {
        logger->log("\n");
    }
}

void Customer::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        createCustomer(pSender, pReceiver, pExecTime, state);
    });
}