#include "../include/line.h"

NodeId_t Line::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addToLine", pReceiver));
    stateShop->custInLines[pReceiver].push(pExecTime);
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    if (stateShop->custInLines[pReceiver].size() == 1) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
    return -1;
}

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

NodeId_t Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromShop\n", pReceiver));
    sendMessage(4, pExecTime, pReceiver, 3);
    return -1;
}

NodeId_t Line::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: hasCustomer\n", pReceiver));
    if (stateShop->custInLines[pReceiver].size() > 0) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
    return -1;
}

void Line::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        addToLine(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        removeFromShop(pSender, pReceiver, pExecTime, state);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        hasCustomer(pSender, pReceiver, pExecTime, state);
    });
}

void Line::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
}
