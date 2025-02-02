#include "line.h"

void Line::addToLine(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": addToLine";
    custInLine += 1;
    std::cout << "  [" << custInLine << "]" << std::endl;
    if (custInLine == 1) {
        sendMessage(1, pExecTime, pReceiver, pReceiver + 2);
    }
}

void Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": removeFromLine";
    custInLine -= 1;
    std::cout << "  [" << custInLine << "]" << std::endl;
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
}

void Line::removeFromShop(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": removeFromShop" << std::endl;
    sendMessage(4, pExecTime, pReceiver, 3);
}

void Line::hasCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    std::cout << pReceiver << ": hasCustomer" << std::endl;
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
