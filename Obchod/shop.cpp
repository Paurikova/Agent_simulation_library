#include "shop.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iostream>  // For std::cout

//functions
void shop::newCustomer(int pSender, SimTime_t pExecTime) {
    nCustomers += 1;
    int random_number = rand() % 5 + 5;
    std::cout << "New Customers. Current[" << nCustomers << "]" << std::endl;
    std::cout << "Shopping time: " << random_number << std::endl;
    sendMessage(3,pExecTime + random_number, pSender,4);
    if (nCustomers == 1) {
        sendMessage(3, pExecTime, pSender, 5, 1);
    }
}

void shop::removedCustomer(int pSender, SimTime_t pExecTime) {
    nCustomers -= 1;
    std::cout << "Out Customer: Current[" << nCustomers << "]" << std::endl;
    sendMessage(3, pExecTime + 1, pSender, 5, 1);
    sendMessage(4, pExecTime + 1, pSender, 5, 1);
}

void shop::addToLine(int pSender, SimTime_t pExecTime) {

}

void shop::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        newCustomer(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        newCustomer(pSender, pExecTime);
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