#include "cash.h"

void Cash::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    if (!hasCustom) {
        //Has break?
        int brakTime = hasBreak(0, pExecTime);
        if (brakTime > -1 ) {
            //has break
            std::cout << "Break" << std::endl;
            //accept customer after break
            sendMessage(2, brakTime + breakLength, pReceiver, pSender);
        }
        // The cash accept customer
        sendMessage(2, pExecTime, pReceiver, pSender);
    }
}

void Cash::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    hasCustom = true;
    //process customer
    std::cout << "Cash processing [" << processLength << "]" << std::endl;
    sendMessage(3, pExecTime + processLength, pReceiver, pReceiver);
}

void Cash::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    hasCustom = true;
    std::cout << "Cash free" << std::endl;
    sendMessage(3, pExecTime, pReceiver, pReceiver - 2);
}

void Cash::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        acceptCustomer(pSender, pReceiver, pExecTime);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        processCustomer(pSender, pReceiver, pExecTime);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        endCustomer(pSender, pReceiver, pExecTime);
    });
}

int Cash::hasBreak(int value) {
    // Loop through each row
    for (int j = 0; j < 2; ++j) {
        // Check if the current element is 200
        if (breaks[j] >= value && breaks[j] + breakLength[j] <= value) {
            return breaks[j];
        }
    }
    return -1;
}
