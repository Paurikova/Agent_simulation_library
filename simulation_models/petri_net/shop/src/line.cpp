#include "../include/line.h"

//1
NodeId_t Line::addToLine_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addToLine_cond1", pReceiver));
    stateShop->custInLines[pReceiver].push(pExecTime);
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    if (stateShop->custInLines[pReceiver].size() == 1) {
        return 5;
    }
    return -1;
}

//5
NodeId_t Line::addToLine_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addToLine_fun1\n", pReceiver));
    sendMessage(1, pExecTime, pReceiver, pReceiver + 2, -1 , new StateBreak());
    return -1;
}

//2
NodeId_t Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromLine", pReceiver));
    stateShop->totalCustTimeInLine[pReceiver] = pExecTime - stateShop->custInLines[pReceiver].front();
    stateShop->totalCustInLine[pReceiver]++;
    stateShop->custInLines[pReceiver].pop();
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
    return -1;
}

//3
NodeId_t Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromShop\n", pReceiver));
    sendMessage(4, pExecTime, pReceiver, 3);
    return -1;
}

//4
NodeId_t Line::hasCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: hasCustomer_cond1\n", pReceiver));
    if (stateShop->custInLines[pReceiver].size() > 0) {
        return 6;
    }
    return -1;
}

//6
NodeId_t Line::hasCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: hasCustomer_fun1\n", pReceiver));
    sendMessage(1, pExecTime, pReceiver, pReceiver + 2, -1, new StateBreak());
    return -1;
}

//5
void Line::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        addToLine_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        removeFromShop(pSender, pReceiver, pExecTime, state);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        hasCustomer_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        addToLine_fun1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(6, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        hasCustomer_fun1(pSender, pReceiver, pExecTime, state);
    });
}

void Line::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
}
