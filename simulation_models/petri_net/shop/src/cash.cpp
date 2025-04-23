#include "../include/cash.h"
#include "../include/state_line.h"
//1
NodeId_t Cash::acceptCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer_cond1 (Line {})\n", pReceiver, stateLine->line));

    std::queue<float> &line = (stateLine->line == 0) ? stateShop->custInLine0 : stateShop->custInLine1;

    if (!(stateLine->line == 0 ? hasCustom1 : hasCustom2)) {
        return 4;
    }
    return 5;
}

//4
NodeId_t Cash::acceptCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer_fun1 (Line {})\n", pReceiver, stateLine->line));
    sendMessage(2, pExecTime, pReceiver, 4, -1, stateLine);  // Customer accepted by cash
    return -1;
}

//5
NodeId_t Cash::acceptCustomer_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer_fun2 (Line {})\n", pReceiver, stateLine->line));
    delete state;
    return -1;
}

//2
NodeId_t Cash::processCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer_cond1 (Line {})", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        return 6;
    } else {
        return 7;
    }
}

//6
NodeId_t Cash::processCustomer_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: processCustomer_code1 (Line {})", pReceiver, stateLine->line));
    hasCustom1 = true;
    return 8;
}

//7
NodeId_t Cash::processCustomer_code3(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: processCustomer_code2 (Line {})\n", pReceiver, stateLine->line));
    hasCustom2 = true;
    return 8;
}

//8
NodeId_t Cash::processCustomer_cond2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer_cond2 (Line {})\n", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        return 9;
    } else {
        return 10;
    }
}

//9
NodeId_t Cash::processCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: processCustomer_fun1 (Line {})\n", pReceiver, state));
    // Process the customer
    logger->log(fmt::format("  [{}]\n", processLength1));
    sendMessage(3, pExecTime + processLength1 , pReceiver, pReceiver, -1, state);
    return -1;
}

//10
NodeId_t Cash::processCustomer_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: processCustomer_fun2 (Line {})\n", pReceiver, state));
    // Process the customer
    logger->log(fmt::format("  [{}]\n", processLength2));
    sendMessage(3, pExecTime + processLength2 , pReceiver, pReceiver, -1, state);
    return -1;
}

//3
NodeId_t Cash::endCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_cond1 (Line {})\n", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        return 11;
    } else {
        return 12;
    }
}

//11
NodeId_t Cash::endCustomer_code1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_code1 (Line {})\n", pReceiver, stateLine->line));
    hasCustom1 = false;
    return 13;
}

//12
NodeId_t Cash::endCustomer_code2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_code2 (Line {})\n", pReceiver, stateLine->line));
    hasCustom2 = false;
    sendMessage(4, pExecTime, pReceiver, 3, -1, stateLine);
    return 13;
}

//13
NodeId_t Cash::endCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_fun1 (Line {})\n", pReceiver, stateLine->line));
    sendMessage(4, pExecTime, pReceiver, 3, -1, stateLine);
    return -1;
}

void Cash::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return acceptCustomer_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return processCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return endCustomer(pSender, pReceiver, pExecTime, state);
    });
}

void Cash::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
}
