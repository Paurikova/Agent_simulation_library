#include "cash_register.h"
void cash_register::processCustomer1(int pSender, SimTime_t pExecTime) {
    int break_ = hasBreak(0, pExecTime);
    if (break_ > -1 ) {
        //has breaking
        std::cout << "Break 1" << std::endl;
        return;
    }
    customers[0] = true;
    sendMessage(1, pExecTime + customer_processing[0], 5, 4);
    //process customer
    std::cout << "Casch 1 Time: " << customer_processing[0] << std::endl;
    sendMessage(3, pExecTime + customer_processing[0], 5, 5);
}

void cash_register::processCustomer2(int pSender, SimTime_t pExecTime) {
    int break_ = hasBreak(1, pExecTime);
    if (break_ > -1 ) {
        //has breaking
        std::cout << "Break 2" << std::endl;
        return;
    }
    customers[1] = true;
    sendMessage(2, pExecTime + customer_processing[1], 5, 4);
    //process customer
    std::cout << "Casch 2 Time: " << customer_processing[1] << std::endl;
    sendMessage(4, pExecTime + customer_processing[1], 5, 5);
}

void cash_register::endCustomer1(int pSender, SimTime_t pExecTime) {
    customers[0] = false;
    sendMessage(2, pExecTime, 5, 3);
}

void cash_register::endCustomer2(int pSender, SimTime_t pExecTime) {
    customers[1] = false;
    sendMessage(3, pExecTime, 5, 3);
}

void cash_register::hasCustomer1(int pSender, SimTime_t pExecTime) {
    if (!customers[0]) {
        sendMessage(4, pExecTime, 5, 3);
    }
}

void cash_register::hasCustomer2(int pSender, SimTime_t pExecTime) {
    if (!customers[1]) {
        sendMessage(5, pExecTime, 5, 3);
    }
}


void cash_register::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        processCustomer1(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        processCustomer2(pSender, pExecTime);
    });
    registerFunction(3, [this](int pSender, SimTime_t pExecTime) {
        endCustomer1(pSender, pExecTime);
    });
    registerFunction(4, [this](int pSender, SimTime_t pExecTime) {
        endCustomer2(pSender, pExecTime);
    });
    registerFunction(5, [this](int pSender, SimTime_t pExecTime) {
        hasCustomer1(pSender, pExecTime);
    });
    registerFunction(6, [this](int pSender, SimTime_t pExecTime) {
        hasCustomer2(pSender, pExecTime);
    });
}

int cash_register::hasBreak(int cache, int value) {
    // Loop through each row
    for (int j = 0; j < 2; ++j) {
        // Check if the current element is 200
        if (arr[cache][j] >= value && arr[cache][j] + breaking_long[cache] <= value) {
            return arr[cache][j];
        }
    }
    return -1;
}
