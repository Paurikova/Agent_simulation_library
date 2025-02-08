#include "../include/cash.h"

NodeId_t Cash::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer", pReceiver));
    if (!hasCustom) {
        //Has break?
        int breakTime = hasBreak(pExecTime);
        if (breakTime > -1 ) {
            //has break
            logger->log(fmt::format("       Break [{}] [{}]\n", pReceiver, breakTime));
            //accept customer after break
            sendMessage(2, breakTime + breakLength, pReceiver, pSender);
            return -1;
        }
        logger->log("\n");
        // The cash accept customer
        sendMessage(2, pExecTime, pReceiver, pSender);
    }
    return -1;
}

NodeId_t Cash::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: processCustomer", pReceiver));
    hasCustom = true;
    //process customer
    logger->log(fmt::format("  [{}]\n" , processLength));
    sendMessage(3, pExecTime + processLength, pReceiver, pReceiver);
    return -1;
}

NodeId_t Cash::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: endCustomer\n", pReceiver));
    hasCustom = false;
    sendMessage(3, pExecTime, pReceiver, pReceiver - 2);
    return -1;
}

void Cash::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        processCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        endCustomer(pSender, pReceiver, pExecTime, state);
    });
}

void Cash::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
}

int Cash::hasBreak(int value) {
    // Loop through each row
    for (int j = 0; j < 2; ++j) {
        // Check if the current element is 200
        if (breaks[j] >= value && breaks[j] + breakLength <= value) {
            return breaks[j];
        }
    }
    return -1;
}
