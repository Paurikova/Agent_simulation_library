#include "../include/cash.h"

//1
NodeId_t Cash::acceptCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer_cond1\n", pReceiver));
    if (!hasCustom) {
        return 4;
    }
    return -1;
}

//4
NodeId_t Cash::acceptCustomer_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer_code1\n", pReceiver));
    //Has break?
    int breakTime = -1;
    // Loop through each row
    for (int j = 0; j < 2; ++j) {
        // Check if the current element is 200
        if (breaks[j] >= pExecTime && breaks[j] + breakLength <= pExecTime) {
            breakTime = breaks[j];
            break;
        }
    }
    state = new StateBreak(breakTime);
    return 5;
}

//5
NodeId_t Cash::acceptCustomer_cond2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer_cond2\n", pReceiver));
    StateBreak* breakTime = dynamic_cast<StateBreak*>(state);
    if (breakTime->cashBreak > -1 ) {
        return 6;
    } else {
        return 7;
    }
}

//6
NodeId_t Cash::acceptCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateBreak* cashBreak = dynamic_cast<StateBreak*>(state);
    logger->log(fmt::format("{}: acceptCustomer_fun1", pReceiver));
    //has break
    logger->log(fmt::format("       Break [{}] [{}]\n", pReceiver, cashBreak->cashBreak));
    //accept customer after break
    sendMessage(2, cashBreak->cashBreak + breakLength, pReceiver, pSender);
    return -1;
}

//7
NodeId_t Cash::acceptCustomer_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer_fun2", pReceiver));
    // The cash accept customer
    sendMessage(2, pExecTime, pReceiver, pSender);
    return -1;
}

//2
NodeId_t Cash::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: processCustomer\n", pReceiver));
    hasCustom = true;
    //process customer
    logger->log(fmt::format("  [{}]\n" , processLength));
    sendMessage(3, pExecTime + processLength, pReceiver, pReceiver);
    return -1;
}

//3
NodeId_t Cash::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: endCustomer\n", pReceiver));
    hasCustom = false;
    sendMessage(3, pExecTime, pReceiver, pReceiver - 2);
    return -1;
}

void Cash::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        processCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        endCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer_code1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer_cond2(pSender, pReceiver, pExecTime, state);
    });
    registerNode(6, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer_fun1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(7, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer_fun2(pSender, pReceiver, pExecTime, state);
    });
}

void Cash::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
}
