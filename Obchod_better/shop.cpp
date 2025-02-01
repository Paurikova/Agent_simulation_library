#include "shop.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iostream>  // For std::cout

//functions
void shop::newCustomer(int pSender, SimTime_t pExecTime) {
    int random_number = rand() % 5 + 5;
    nCustomers += 1;
    std::cout << "New Customers. Shopping time: " << random_number << " Current[" << nCustomers << "]" << std::endl;
    std::cout << "Shopping time: " << random_number << std::endl;
    sendMessage(3,pExecTime + random_number, 3,4);
}

void shop::removedCustomerLine1(int pSender, SimTime_t pExecTime) {
    nCustomers -= 1;
    sendMessage(4, pExecTime+1, 3, 3);
    std::cout << "Out Customer Line 1: Current[" << nCustomers << "]" << std::endl;
}

void shop::removedCustomerLine2(int pSender, SimTime_t pExecTime) {
    nCustomers -= 1;
    sendMessage(5, pExecTime+1, 3, 3);
    std::cout << "Out Customer Line 2: Current[" << nCustomers << "]" << std::endl;
}

void shop::hasCustomers1(int pSender, SimTime_t pExecTime) {
    if (nCustomers > 0) {
        sendMessage(4, pExecTime, 1, 4);
    }
}

void shop::hasCustomers2(int pSender, SimTime_t pExecTime) {
    if (nCustomers > 0) {
        sendMessage(5, pExecTime, 1, 4);
    }
}

void shop::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        newCustomer(pSender, int pReceiver, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        removedCustomerLine1(pSender, pExecTime);
    });
    registerFunction(3, [this](int pSender, SimTime_t pExecTime) {
        removedCustomerLine2(pSender, pExecTime);
    });
    registerFunction(4, [this](int pSender, SimTime_t pExecTime) {
        hasCustomers1(pSender, pExecTime);
    });
    registerFunction(5, [this](int pSender, SimTime_t pExecTime) {
        hasCustomers2(pSender, pExecTime);
    });
}

void shop::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    sendMessage(1, 0, 1, 2);
}