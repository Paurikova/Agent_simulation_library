#include "../include/line.h"

void Line::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addToLine", pReceiver));
    stateShop->custInLines[pReceiver].push(pExecTime);
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    if (stateShop->custInLines[pReceiver].size() == 1) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
        return;
    }
}

void Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromLine", pReceiver));
    stateShop->totalCustTimeInLine[pReceiver] += pExecTime - stateShop->custInLines[pReceiver].front();
    std::cout << stateShop->totalCustTimeInLine[pReceiver] << std::endl;
    stateShop->totalCustInLine[pReceiver]++;
    stateShop->custInLines[pReceiver].pop();
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
}

void Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromShop\n", pReceiver));
    sendMessage(4, pExecTime, pReceiver, 3);
}

void Line::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: hasCustomer\n", pReceiver));
    if (stateShop->custInLines[pReceiver].size() > 0) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        addToLine(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeFromShop(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        hasCustomer(pSender, pReceiver, pExecTime, state);
    });
}
