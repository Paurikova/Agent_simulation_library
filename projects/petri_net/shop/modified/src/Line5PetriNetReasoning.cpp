#include "../include/Line5PetriNetReasoning.h"
NodeId_t Line5PetriNetReasoning::hasCustomer_fun1_fun363(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: hasCustomer_fun1_fun363\n", pReceiver));
    sendMessage(1, pExecTime, pReceiver, pReceiver + 2, -1, new StateBreak());
    return -1;
}
NodeId_t Line5PetriNetReasoning::Condition_cond358(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: Condition_cond358\n", pReceiver));
    if (stateShop->custInLines[pReceiver].size() > 0) {
        //add your code
        return 363;
    } else {
        //add your code
        return -1;
    }
}
NodeId_t Line5PetriNetReasoning::removeFromShop_fun355(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: removeFromShop_fun355\n", pReceiver));
    sendMessage(4, pExecTime, pReceiver, 3);
    return -1;
}
NodeId_t Line5PetriNetReasoning::removeFromLine_fun352(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: removeFromLine_fun352", pReceiver));
    stateShop->totalCustTimeInLine[pReceiver] = pExecTime - stateShop->custInLines[pReceiver].front();
    stateShop->totalCustInLine[pReceiver]++;
    stateShop->custInLines[pReceiver].pop();
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
    return -1;
}
NodeId_t Line5PetriNetReasoning::addToLine_fun1_fun349(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: addToLine_fun1_fun349\n", pReceiver));
    sendMessage(1, pExecTime, pReceiver, pReceiver + 2, -1 , new StateBreak());
    return -1;
}
NodeId_t Line5PetriNetReasoning::Condition_cond344(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: Condition_cond344", pReceiver));
    stateShop->custInLines[pReceiver].push(pExecTime);
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    if (stateShop->custInLines[pReceiver].size() == 1) {
        //add your code
        return 349;
    } else {
        //add your code
        return -1;
    }
}

void Line5PetriNetReasoning::registerNodes() {
    //registration
    registerNode(363, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return hasCustomer_fun1_fun363(pSender, pReceiver, pExecTime, state);
    });
    registerNode(358, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond358(pSender, pReceiver, pExecTime, state);
    });
    registerNode(355, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeFromShop_fun355(pSender, pReceiver, pExecTime, state);
    });
    registerNode(352, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeFromLine_fun352(pSender, pReceiver, pExecTime, state);
    });
    registerNode(349, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addToLine_fun1_fun349(pSender, pReceiver, pExecTime, state);
    });
    registerNode(344, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond344(pSender, pReceiver, pExecTime, state);
    });
}

void Line5PetriNetReasoning::registerServices() {
    //services
    registerService(4, 358);
    registerService(3, 355);
    registerService(2, 352);
    registerService(1, 344);
}