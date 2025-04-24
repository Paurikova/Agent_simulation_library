//TODO include
#include "Shop4PetriNetReasoning.h"
NodeId_t Shop4PetriNetReasoning::addCustomerToLine_fun180(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Shop4PetriNetReasoning::removeCustomer_fun2_fun177(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Shop4PetriNetReasoning::removeCustomer_fun1_fun174(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Shop4PetriNetReasoning::Condition_cond169(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 174;
    } else {
        //add your code
        return 177;
    }
}
NodeId_t Shop4PetriNetReasoning::newCustomer_fun166(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Shop4PetriNetReasoning::close_fun163(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Shop4PetriNetReasoning::open_fun160(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}

void Shop4PetriNetReasoning::registerNodes() {
    //registration
    registerNode(180, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addCustomerToLine_fun180(pSender, pReceiver, pExecTime, state);
    });
    registerNode(177, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeCustomer_fun2_fun177(pSender, pReceiver, pExecTime, state);
    });
    registerNode(174, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeCustomer_fun1_fun174(pSender, pReceiver, pExecTime, state);
    });
    registerNode(169, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond169(pSender, pReceiver, pExecTime, state);
    });
    registerNode(166, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return newCustomer_fun166(pSender, pReceiver, pExecTime, state);
    });
    registerNode(163, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return close_fun163(pSender, pReceiver, pExecTime, state);
    });
    registerNode(160, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return open_fun160(pSender, pReceiver, pExecTime, state);
    });
}

void Shop4PetriNetReasoning::registerServices() {
    //services
    registerService(5, 180);
    registerService(4, 169);
    registerService(3, 166);
    registerService(2, 163);
    registerService(1, 160);
}