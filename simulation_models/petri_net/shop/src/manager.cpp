#include "../include/manager.h"
#include <cmath>  // For fmod()

//functions
NodeId_t Manager::generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: generateCustomer\n", pReceiver));
    // is window open?
    if (!run) {
        return -1;
    }
    //create msg for new customer generating
    sendMessage(1, pExecTime, pReceiver, 2);
    //generate new customer based on generating time
    sendMessage(1, pExecTime + newCust, pReceiver, pReceiver);
    return -1;
}

NodeId_t Manager::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: acceptCustomer\n", pReceiver));
    sendMessage(3, pExecTime, pReceiver, 3);
    return -1;
}

NodeId_t Manager::closeSimulation(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    run = false;
    return -1;
}

void Manager::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        generateCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        acceptCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        closeSimulation(pSender, pReceiver, pExecTime, state);
    });
}

void Manager::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
}

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    //open
    sendMessage(1, 0, 1, 3);
    //close
    //sendMessage(2, end, 1, 3);
    //window
    sendMessage(1, 0, 1, 8);
    // new customer
    sendMessage(1, 0, 1, 1);

}