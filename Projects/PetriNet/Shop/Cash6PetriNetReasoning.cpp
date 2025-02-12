//TODO incluce
#include "Cash6PetriNetReasoning.h"
NodeId_t Cash6PetriNetReasoning::endCustomer_fun389() {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::processCustomer_fun386() {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::acceptCustomerFun2_fun383() {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::acceptCustomer_fun1_fun380() {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond375() {
    if () {
        //add your code
        return 380;
    } else {
        //add your code
        return 383;
    }
}
NodeId_t Cash6PetriNetReasoning::Code_code371() {
    //add your code
    return 375;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond366() {
    if () {
        //add your code
        return 371;
    } else {
        //add your code
        return -1;
    }
}

void Cash6PetriNetReasoning::registerNodes() {
    //registration
    registerNode(389, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return endCustomer_fun389(pSender, pReceiver, pExecTime, state);
    });
    registerNode(386, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return processCustomer_fun386(pSender, pReceiver, pExecTime, state);
    });
    registerNode(383, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return acceptCustomerFun2_fun383(pSender, pReceiver, pExecTime, state);
    });
    registerNode(380, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return acceptCustomer_fun1_fun380(pSender, pReceiver, pExecTime, state);
    });
    registerNode(375, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return Condition_cond375(pSender, pReceiver, pExecTime, state);
    });
    registerNode(371, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return Code_code371(pSender, pReceiver, pExecTime, state);
    });
    registerNode(366, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return Condition_cond366(pSender, pReceiver, pExecTime, state);
    });
}

void Cash6PetriNetReasoning::registerServices() {
    //services
    registerService(3, 389);
    registerService(2, 386);
    registerService(1, 366);
}