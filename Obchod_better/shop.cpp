#include "shop.h"
#include <cstdlib>
#include <iostream>

//functions
void Shop::open(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: open", pReceiver));
    logger->log("   Shopping is open\n");
}

void Shop::close(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: close", pReceiver));
    logger->log("   Shop is close\n");
}

void Shop::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: newCustomer", pReceiver));
    nCustomers += 1;
    int shoppingTime = rand() % shopping + shopping;
    logger->log(fmt::format( "[{}]  Shopping time [{}]\n", nCustomers, shoppingTime));
    sendMessage(5,pExecTime + shoppingTime, pReceiver, pReceiver);
}

void Shop::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: removeCustomer", pReceiver));
    nCustomers -= 1;
    logger->log(fmt::format("  [{}]\n", nCustomers));
    if (nCustomers > 0) {
        sendMessage(4, pExecTime + 1, pReceiver, pSender);
    }
}

void Shop::addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    logger->log(fmt::format("{}: addCustomerToLine", pReceiver));
    logger->log(fmt::format("   Line1[{}]     Line2 [{}]\n", custInLines[0]->custInLine, custInLines[1]->custInLine));
    if (custInLines[0]->custInLine >= custInLines[1]->custInLine) {
        sendMessage(1,pExecTime, pReceiver,5);
    } else {
        sendMessage(1,pExecTime, pReceiver,4);
    }
}

void Shop::registerFunctions() {
    // Register a lambda function to handle function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        open(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        close(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        newCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        removeCustomer(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
        addCustomerToLine(pSender, pReceiver, pExecTime, args);
    });
}