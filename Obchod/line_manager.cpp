#include "line_manager.h"

void line_manager::addToLine(int pSender, SimTime_t pExecTime) {
    if (arr[0] < arr[1]) {
        arr[0] += 1;
        sendMessage(3, pExecTime, pSender, 5);
    } else {
        arr[1] += 1;
        sendMessage(4, pExecTime, pSender, 5);
    }
    std::cout << "Lines: 1[" << arr[0] << "] 2[" << arr[1] << "]" << std::endl;
}


void line_manager::removeFromLine1(int pSender, SimTime_t pExecTime) {
    if (arr[0] > 0) {
        arr[0] -= 1;
        sendMessage(1, pExecTime, pSender, 5);
    }
}

void line_manager::removeFromLine2(int pSender, SimTime_t pExecTime) {
    if (arr[0] > 0) {
        arr[1] -= 1;
        sendMessage(2, pExecTime, pSender, 5);
    }
}

void line_manager::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        removeFromLine1(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        removeFromLine2(pSender, pExecTime);
    });
    registerFunction(3, [this](int pSender, SimTime_t pExecTime) {
        addToLine(pSender, pExecTime);
    });
}
