#include "../include/shop.h"
#include <cstdlib>
#include "../include/state_line.h"

// Functions
void Shop::open(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: open", pReceiver));
    logger->log("   Shopping is open\n");
}

void Shop::close(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: close", pReceiver));
    logger->log("   Shop is close\n");
}

void Shop::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: newCustomer", pReceiver));
    stateShop->custInShop += 1;
    int shoppingTime = rand() % shopping + shopping;
    stateShop->shoppingTime += shoppingTime;
    logger->log(fmt::format("[{}]  Shopping time [{}]\n", stateShop->custInShop, shoppingTime));
    sendMessage(5, pExecTime + shoppingTime, pReceiver, pReceiver);
}

void Shop::removeCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeCustomer", pReceiver));
    stateShop->custInShop -= 1;
    logger->log(fmt::format("  [{}]\n", stateShop->custInShop));
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    if (stateLine->line == 0 ? (stateShop->custInLine0.size() > 0)
    : (stateShop->custInLine1.size() > 0)) {
        sendMessage(1, pExecTime + 1, pReceiver, 5, 1, state);
        return;
    }
    delete state;
}

void Shop::addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: addCustomerToLine", pReceiver));
    logger->log(fmt::format("   Line 0 [{}]     Line 1 [{}]\n", stateShop->custInLine0.size(), stateShop->custInLine1.size()));
    sendMessage(1, pExecTime, pReceiver, pReceiver+1);
}


void Shop::registerFunctions() {
    // Register the lambdas for each function
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        open(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        close(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        newCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        addCustomerToLine(pSender, pReceiver, pExecTime, state);
    });
}
