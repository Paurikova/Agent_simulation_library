#include "line.h"

void Line::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addToLine", pReceiver));
    stateShop->custInLine[pReceiver == 4 ? 0 : 1]++;
    stateShop->totalCustInLine[pReceiver == 4 ? 0 : 1]++;
    logger->log(fmt::format("  [{}]\n", stateShop->custInLine[pReceiver == 4 ? 0 : 1]));
    if (stateShop->custInLine[pReceiver == 4 ? 0 : 1] == 1) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromLine", pReceiver));
    stateShop->custInLine[pReceiver == 4 ? 0 : 1]--;
    logger->log(fmt::format("  [{}]\n", stateShop->custInLine[pReceiver == 4 ? 0 : 1]));
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
}

void Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromShop\n", pReceiver));
    sendMessage(4, pExecTime, pReceiver, 3);
}

void Line::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: hasCustomer\n", pReceiver));
    if (stateShop->custInLine[pReceiver == 4 ? 0 : 1] > 0) {
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
