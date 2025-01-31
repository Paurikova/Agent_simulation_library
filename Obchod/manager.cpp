#include "manager.h"
#include <cmath>  // For fmod()

//functions
void Manager::newCustomer(int pSender, SimTime_t pExecTime) {
    if (fmod(static_cast<double>(pExecTime), 15.0) == 0.0) {
        //create msg for new customer generating
        sendMessage(1, pExecTime, pSender, 2);
    }
    if (pExecTime < shopClose) {
        sendMessage(1, pExecTime + 1, pSender, 1);
    }
}

void Manager::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        newCustomer(pSender, pExecTime);
    });
}

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    sendMessage(1, 0, 1, 1);
}