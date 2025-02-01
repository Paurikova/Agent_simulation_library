#include "manager.h"
#include <cmath>  // For fmod()

//functions
void Manager::generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime) {
    if (pExecTime > end) {
        return;
    }
    //create msg for new customer generating
    sendMessage(1, pExecTime, pReceiver);
    //generate new customer based on generating time
    sendMessage(1, pExecTime + new_c, pReceiver, pReceiver);
}

void Manager::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime) {
        generateCustomer(pSender, pReceiver, pExecTime);
    });
}

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    // new customer
    sendMessage(1, 0, 1, 1);
}