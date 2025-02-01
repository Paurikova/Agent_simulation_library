#include "line_manager.h"

void line_manager::addToLine(int pSender, SimTime_t pExecTime) {
    if (arr[0] < arr[1]) {
        arr[0] += 1;
    } else {
        arr[1] += 1;
    }
    std::cout << "Added Lines: 1[" << arr[0] << "] 2[" << arr[1] << "]" << std::endl;
}

void line_manager::hasCustomer1(int pSender, SimTime_t pExecTime) {
    if (arr[0] > 0) {
        sendMessage(1, pExecTime, 4, 5);
    } else {
        sendMessage(2, pExecTime + 1, 4, 1);
    }
}

void line_manager::hasCustomer2(int pSender, SimTime_t pExecTime) {
    if (arr[1] > 0) {
        sendMessage(2, pExecTime, 4, 5);
    } else {
        sendMessage(3, pExecTime + 1, 4, 1);
    }
}


void line_manager::removeFromLine1(int pSender, SimTime_t pExecTime) {
    if (arr[0] > 0) {
        arr[0] -= 1;
        std::cout << "Removed Lines: 1[" << arr[1] << "]" << std::endl;
    }
}

void line_manager::removeFromLine2(int pSender, SimTime_t pExecTime) {
    if (arr[1] > 0) {
        arr[1] -= 1;
        std::cout << "Removed Lines: 2[" << arr[1] << "]" << std::endl;
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
    registerFunction(4, [this](int pSender, SimTime_t pExecTime) {
        hasCustomer1(pSender, pExecTime);
    });
    registerFunction(5, [this](int pSender, SimTime_t pExecTime) {
        hasCustomer2(pSender, pExecTime);
    });
}
