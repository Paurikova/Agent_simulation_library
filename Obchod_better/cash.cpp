#include "cash.h"

void Cash::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    std::cout << pReceiver << ": acceptCustomer" << std::endl;
    if (!hasCustom) {
        //Has break?
        int brakTime = hasBreak(pExecTime);
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

void Cash::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    std::cout << pReceiver << ": processCustomer";
    hasCustom = true;
    //process customer
    std::cout << "  [" << processLength << "]" << std::endl;
    sendMessage(3, pExecTime + processLength, pReceiver, pReceiver);
}

void Cash::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    std::cout << pReceiver << ": endCustomer" << std::endl;
    hasCustom = false;
    sendMessage(3, pExecTime, pReceiver, pReceiver - 2);
}

void Cash::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        acceptCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        processCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
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
