#include "cash.h"

void Cash::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: acceptCustomer", pReceiver));
    if (!hasCustom) {
        //Has break?
        int breakTime = hasBreak(pExecTime);
        if (breakTime > -1 ) {
            //has break
            logger->log(fmt::format("       Break [{}] [{}]\n", pReceiver, breakTime));
            //accept customer after break
            sendMessage(2, breakTime + breakLength, pReceiver, pSender);
            return;
        }
        logger->log("\n");
        // The cash accept customer
        sendMessage(2, pExecTime, pReceiver, pSender);
    }
}

void Cash::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: processCustomer", pReceiver));
    hasCustom = true;
    //process customer
    logger->log(fmt::format("  [{}]\n" , processLength));
    sendMessage(3, pExecTime + processLength, pReceiver, pReceiver);
}

void Cash::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: endCustomer\n", pReceiver));
    hasCustom = false;
    sendMessage(3, pExecTime, pReceiver, pReceiver - 2);
}

void Cash::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        acceptCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        processCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        endCustomer(pSender, pReceiver, pExecTime, args);
    });
}

int Cash::hasBreak(int value) {
    // Loop through each row
    for (int j = 0; j < 2; ++j) {
        // Check if the current element is 200
        if (breaks[j] >= value && breaks[j] + breakLength <= value) {
            return breaks[j];
        }
    }
    return -1;
}
