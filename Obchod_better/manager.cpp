#include "manager.h"
#include <cmath>  // For fmod()

//functions
void Manager::generateCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    std::cout << pReceiver << ": generateCustomer" << std::endl;
    // Is shop open?
    if (pExecTime >= end) {
        return;
    }
    //create msg for new customer generating
    sendMessage(1, pExecTime, pReceiver, 2);
    //generate new customer based on generating time
    sendMessage(1, pExecTime + newCust, pReceiver, pReceiver);
}

void Manager::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    std::cout << pReceiver << ": acceptCustomer" << std::endl;
    sendMessage(3, pExecTime, pReceiver, 3);
}

void Manager::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        generateCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
        acceptCustomer(pSender, pReceiver, pExecTime, args);
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
    //close
    sendMessage(2, end, 1, 3);
    // new customer
    sendMessage(1, 0, 1, 1);

}