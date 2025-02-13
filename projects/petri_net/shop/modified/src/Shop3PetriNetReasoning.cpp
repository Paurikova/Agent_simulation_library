#include "../include/Shop3PetriNetReasoning.h"
#include <cstdlib>
NodeId_t Shop3PetriNetReasoning::addCustomerToLine_fun2_fun341(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: addCustomerToLine_fun2_fun341\n", pReceiver));
    sendMessage(1,pExecTime, pReceiver,4);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::addCustomerToLine_fun1_fun338(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: addCustomerToLine_fun1_fun338\n", pReceiver));
    sendMessage(1,pExecTime, pReceiver,5);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::Condition_cond333(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: Condition_cond333", pReceiver));
    logger->log(fmt::format("   Line1[{}]     Line2[{}]\n", stateShop->custInLines[4].size(), stateShop->custInLines[5].size()));
    if (stateShop->custInLines[4].size() >= stateShop->custInLines[5].size()) {
        //add your code
        return 338;
    } else {
        //add your code
        return 341;
    }
}
NodeId_t Shop3PetriNetReasoning::removeCustomer_fun1_fun330(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: removeCustomer_fun1_fun330", pReceiver));
    sendMessage(4, pExecTime + 1, pReceiver, pSender);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::Condition_cond325(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: Condition_cond325", pReceiver));
    stateShop->custInShop -= 1;
    logger->log(fmt::format("  [{}]\n", stateShop->custInShop));
    if (stateShop->custInShop > 0) {
        //add your code
        return 330;
    } else {
        //add your code
        return -1;
    }
}
NodeId_t Shop3PetriNetReasoning::newCustomer_fun322(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: newCustomer_fun322", pReceiver));
    stateShop->custInShop += 1;
    int shoppingTime = rand() % shopping + shopping;
    stateShop->shoppingTime += shoppingTime;
    logger->log(fmt::format( "[{}]  Shopping time [{}]\n", stateShop->custInShop, shoppingTime));
    sendMessage(5,pExecTime + shoppingTime, pReceiver, pReceiver);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::close_fun319(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: close_fun319", pReceiver));
    logger->log("   Shop is close\n");
    return -1;
}
NodeId_t Shop3PetriNetReasoning::open_fun316(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: open_fun316", pReceiver));
    logger->log("   Shopping is open\n");
    return -1;
}

void Shop3PetriNetReasoning::registerNodes() {
    //registration
    registerNode(341, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addCustomerToLine_fun2_fun341(pSender, pReceiver, pExecTime, state);
    });
    registerNode(338, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addCustomerToLine_fun1_fun338(pSender, pReceiver, pExecTime, state);
    });
    registerNode(333, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond333(pSender, pReceiver, pExecTime, state);
    });
    registerNode(330, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeCustomer_fun1_fun330(pSender, pReceiver, pExecTime, state);
    });
    registerNode(325, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond325(pSender, pReceiver, pExecTime, state);
    });
    registerNode(322, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return newCustomer_fun322(pSender, pReceiver, pExecTime, state);
    });
    registerNode(319, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return close_fun319(pSender, pReceiver, pExecTime, state);
    });
    registerNode(316, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return open_fun316(pSender, pReceiver, pExecTime, state);
    });
}

void Shop3PetriNetReasoning::registerServices() {
    //services
    registerService(5, 333);
    registerService(4, 325);
    registerService(3, 322);
    registerService(2, 319);
    registerService(1, 316);
}