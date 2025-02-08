#include "../include/shop.h"
#include <cstdlib>

//functions
NodeId_t Shop::open(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: open", pReceiver));
    logger->log("   Shopping is open\n");
    return -1;
}

NodeId_t Shop::close(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: close", pReceiver));
    logger->log("   Shop is close\n");
    return -1;
}

NodeId_t Shop::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: newCustomer", pReceiver));
    stateShop->custInShop += 1;
    int shoppingTime = rand() % shopping + shopping;
    stateShop->shoppingTime += shoppingTime;
    logger->log(fmt::format( "[{}]  Shopping time [{}]\n", stateShop->custInShop, shoppingTime));
    sendMessage(5,pExecTime + shoppingTime, pReceiver, pReceiver);
    return -1;
}

NodeId_t Shop::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeCustomer", pReceiver));
    stateShop->custInShop -= 1;
    logger->log(fmt::format("  [{}]\n", stateShop->custInShop));
    if (stateShop->custInShop > 0) {
        sendMessage(4, pExecTime + 1, pReceiver, pSender);
    }
    return -1;
}

NodeId_t Shop::addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addCustomerToLine", pReceiver));
    logger->log(fmt::format("   Line1[{}]     Line2[{}]\n", stateShop->custInLines[4].size(), stateShop->custInLines[5].size()));
    if (stateShop->custInLines[4].size() >= stateShop->custInLines[5].size()) {
        sendMessage(1,pExecTime, pReceiver,5);
    } else {
        sendMessage(1,pExecTime, pReceiver,4);
    }
    return -1;
}

void Shop::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        open(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        close(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        newCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        removeCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        addCustomerToLine(pSender, pReceiver, pExecTime, state);
    });
}

void Shop::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
    registerService(5, 5);
}