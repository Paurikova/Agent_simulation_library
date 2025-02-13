#include "../include/shop.h"
#include <cstdlib>

//functions
//1
NodeId_t Shop::open(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: open", pReceiver));
    logger->log("   Shopping is open\n");
    return -1;
}

//2
NodeId_t Shop::close(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: close", pReceiver));
    logger->log("   Shop is close\n");
    return -1;
}

//3
NodeId_t Shop::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: newCustomer", pReceiver));
    stateShop->custInShop += 1;
    int shoppingTime = rand() % shopping + shopping;
    stateShop->shoppingTime += shoppingTime;
    logger->log(fmt::format( "[{}]  Shopping time [{}]\n", stateShop->custInShop, shoppingTime));
    sendMessage(5,pExecTime + shoppingTime, pReceiver, pReceiver);
    return -1;
}

//4
NodeId_t Shop::removeCustomer_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeCustomer_cond1", pReceiver));
    stateShop->custInShop -= 1;
    logger->log(fmt::format("  [{}]\n", stateShop->custInShop));
    if (stateShop->custInShop > 0) {
        return 6;
    }
    return -1;
}

//6
NodeId_t Shop::removeCustomer_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeCustomer_funct1", pReceiver));
    sendMessage(4, pExecTime + 1, pReceiver, pSender);
    return -1;
}

//5
NodeId_t Shop::addCustomerToLine_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addCustomerToLine_cond1", pReceiver));
    logger->log(fmt::format("   Line1[{}]     Line2[{}]\n", stateShop->custInLines[4].size(), stateShop->custInLines[5].size()));
    if (stateShop->custInLines[4].size() >= stateShop->custInLines[5].size()) {
        return  7;
    } else {
        return 8;
    }
}

//7
NodeId_t Shop::addCustomerToLine_fun1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addCustomerToLine_funct1\n", pReceiver));
    sendMessage(1,pExecTime, pReceiver,5);
    return -1;
}

//8
NodeId_t Shop::addCustomerToLine_fun2(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addCustomerToLine_funct2\n", pReceiver));
    sendMessage(1,pExecTime, pReceiver,4);
    return -1;
}

void Shop::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return open(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return close(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return newCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return removeCustomer_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return addCustomerToLine_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(6, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return removeCustomer_fun1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(7, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return addCustomerToLine_fun1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(8, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return addCustomerToLine_fun2(pSender, pReceiver, pExecTime, state);
    });
}

void Shop::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
    registerService(5, 5);
}