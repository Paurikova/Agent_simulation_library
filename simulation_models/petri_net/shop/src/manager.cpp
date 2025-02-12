#include "../include/manager.h"
#include <cmath>  // For fmod()

//functions
void Manager::generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: generateCustomer\n", pReceiver));
    // is window open?
    if (!run) {
        return;
    }
    //create msg for new customer generating
    sendMessage(1, pExecTime, pReceiver, 2);
    //generate new customer based on generating time
    sendMessage(1, pExecTime + newCust, pReceiver, pReceiver);
}

void Manager::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer\n", pReceiver));
    sendMessage(3, pExecTime, pReceiver, 3);
}

void Manager::closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    run = false;
}

void Manager::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        generateCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        acceptCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        closeSimulation(pSender, pReceiver, pExecTime, state);
    });
}

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    //open
    sendMessage(1, 0, 1, 3);
    //window
    sendMessage(1, 0, 1, 8);
    // new customer
    sendMessage(1, 0, 1, 1);

}