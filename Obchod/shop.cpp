#include "shop.h"
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()
#include <iostream>  // For std::cout

//functions
void shop::newCustomer(int pSender, SimTime_t pExecTime) {
    nCustomers += 1;
    srand(static_cast<unsigned int>(time(0)));
    int random_number = rand() % 30 + 5;
    std::cout << "Customers: " << nCustomers << std::endl;
    std::cout << "Shopping time: " << random_number << std::endl;
    sendMessage(3,pExecTime + random_number, pSender,4);
}

void shop::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
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