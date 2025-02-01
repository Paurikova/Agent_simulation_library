#include "cash_register.h"
void cash_register::processCustomer1(int pSender, SimTime_t pExecTime) {
    int break_ = hasBreak(0, pExecTime);
    if (break_ > -1 ) {
        //has breaking
        std::cout << "Break 1" << std::endl;
        return;
    }
    sendMessage(1, pExecTime, 5, 4);
    //process customer
    std::cout << "Casch 1" << std::endl;
    sendMessage(2, pExecTime + customer_processing[0], 5, 3);
}

void cash_register::processCustomer2(int pSender, SimTime_t pExecTime) {
    int break_ = hasBreak(1, pExecTime);
    if (break_ > -1 ) {
        //has breaking
        std::cout << "Break 2" << std::endl;
        return;
    }
    sendMessage(2, pExecTime, 5, 4);
    //process customer
    std::cout << "Casch 2" << std::endl;
    sendMessage(3, pExecTime + customer_processing[1], 5, 3);
}

void cash_register::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        processCustomer1(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        processCustomer2(pSender, pExecTime);
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
