#include "line.h"

void Line::addToLine(int pSender, int pReceiver, SimTime_t pExecTime) {
    custInLine += 1;
    std::cout << "Line [" << custInLine << "]" << std::endl;
    if (custInLine == 1) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime) {
    custInLine -= 1;
    std::cout << "Line [" << custInLine << "]" << std::endl;
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
}

void Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime) {
    sendMessage(2, pExecTime, pReceiver, 3);
}

void Line::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    if (custInLine > 0) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        addToLine(pSender, pReceiver, pExecTime);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        removeFromLine(pSender, pReceiver, pExecTime);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        removeFromShop(pSender, pReceiver, pExecTime);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        hasCustomer(pSender, pReceiver, pExecTime);
    });
}
