//TODO include
#include "../include/Customer2ReactiveReasoning.h"
void Customer2ReactiveReasoning::createCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: createCustomer", pReceiver));
    int isCreated = rand() % 2;
    // Should be new customer created?
    if (isCreated == 1) {
        stateShop->customers += 1;
        logger->log(fmt::format("  [{}]\n", stateShop->customers));
        // new customer is created
        //send him to shop
        sendMessage(2, pExecTime, pReceiver, pSender);
    } else {
        logger->log("\n");
    }
}

void Customer2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        createCustomer(pSender, pReceiver, pExecTime, state);
    });
}