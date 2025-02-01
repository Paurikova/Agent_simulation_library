#include "manager.h"
#include <cmath>  // For fmod()

//functions
void Manager::newCustomer(int pSender, SimTime_t pExecTime) {
    if (pExecTime > shopClose) {
        return;
    }
    //create msg for new customer generating
    sendMessage(1, pExecTime, 1, 2);
    sendMessage(1, pExecTime + 1, 1, 1);
}

void Manager::isOpen1(int pSender, SimTime_t pExecTime) {
    if (pExecTime < shopClose) {
        sendMessage(2, pExecTime, 1, 4);
    } else {
        //has customers
        sendMessage(4, pExecTime, 1, 4);
    }

}

void Manager::isOpen2(int pSender, SimTime_t pExecTime) {
    if (pExecTime < shopClose) {
        sendMessage(5, pExecTime, 1, 4);
    } else {
        //has customers
    }

}

void Manager::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, SimTime_t pExecTime) {
        newCustomer(pSender, pExecTime);
    });
    registerFunction(2, [this](int pSender, SimTime_t pExecTime) {
        isOpen1(pSender, pExecTime);
    });
    registerFunction(3, [this](int pSender, SimTime_t pExecTime) {
        isOpen2(pSender, pExecTime);
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
    sendMessage(2, 0, 1, 1);
    sendMessage(3, 0, 1, 1);
}