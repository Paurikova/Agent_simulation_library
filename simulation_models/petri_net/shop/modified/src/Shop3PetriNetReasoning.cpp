#include "../include/Shop3PetriNetReasoning.h"
#include "../include/state_line.h"
NodeId_t Shop3PetriNetReasoning::addCustomerToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: addCustomerToLine", pReceiver));
    logger->log(fmt::format("   Line 0 [{}]     Line 1 [{}]\n", stateShop->custInLine0.size(), stateShop->custInLine1.size()));
    sendMessage(1, pExecTime, pReceiver, pReceiver+1);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::removeCustomer_fun177(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: removeCustomer_fun177", pReceiver));
    delete state;
    return -1;
}
NodeId_t Shop3PetriNetReasoning::removeCustomer_fun174(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: removeCustomer_fun174", pReceiver));
    sendMessage(1, pExecTime + 1, pReceiver, 5, 1, state);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::removeCustomer_cond169(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeCustomer_cond169", pReceiver));
    stateShop->custInShop -= 1;
    logger->log(fmt::format("  [{}]\n", stateShop->custInShop));
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    if (stateLine->line == 0 ? (stateShop->custInLine0.size() > 0)
                             : (stateShop->custInLine1.size() > 0)) {
        //add your code
        return 174;
    } else {
        //add your code
        return 177;
    }
}
NodeId_t Shop3PetriNetReasoning::newCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: newCustomer", pReceiver));
    stateShop->custInShop += 1;
    int shoppingTime = rand() % shopping + shopping;
    stateShop->shoppingTime += shoppingTime;
    logger->log(fmt::format("[{}]  Shopping time [{}]\n", stateShop->custInShop, shoppingTime));
    sendMessage(5, pExecTime + shoppingTime, pReceiver, pReceiver);
    return -1;
}
NodeId_t Shop3PetriNetReasoning::close(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: close", pReceiver));
    logger->log("   Shop is close\n");
    return -1;
}
NodeId_t Shop3PetriNetReasoning::open(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: open", pReceiver));
    logger->log("   Shopping is open\n");
    return -1;
}

void Shop3PetriNetReasoning::registerNodes() {
    //registration
    registerNode(180, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addCustomerToLine(pSender, pReceiver, pExecTime, state);
    });
    registerNode(177, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeCustomer_fun177(pSender, pReceiver, pExecTime, state);
    });
    registerNode(174, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeCustomer_fun174(pSender, pReceiver, pExecTime, state);
    });
    registerNode(169, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeCustomer_cond169(pSender, pReceiver, pExecTime, state);
    });
    registerNode(166, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return newCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerNode(163, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return close(pSender, pReceiver, pExecTime, state);
    });
    registerNode(160, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return open(pSender, pReceiver, pExecTime, state);
    });
}

void Shop3PetriNetReasoning::registerServices() {
    //services
    registerService(5, 180);
    registerService(4, 169);
    registerService(3, 166);
    registerService(2, 163);
    registerService(1, 160);
}