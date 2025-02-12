//TODO incluce
#include "Shop3PetriNetReasoning.h"
NodeId_t Shop3PetriNetReasoning::addCustomerToLine_fun2_fun341() {
    //add your code
    return -1;
}
NodeId_t Shop3PetriNetReasoning::addCustomerToLine_fun1_fun338() {
    //add your code
    return -1;
}
NodeId_t Shop3PetriNetReasoning::Condition_cond333() {
    if () {
        //add your code
        return 338;
    } else {
        //add your code
        return 341;
    }
}
NodeId_t Shop3PetriNetReasoning::removeCustomer_fun1_fun330() {
    //add your code
    return -1;
}
NodeId_t Shop3PetriNetReasoning::Condition_cond325() {
    if () {
        //add your code
        return 330;
    } else {
        //add your code
        return -1;
    }
}
NodeId_t Shop3PetriNetReasoning::newCustomer_fun322() {
    //add your code
    return -1;
}
NodeId_t Shop3PetriNetReasoning::close_fun319() {
    //add your code
    return -1;
}
NodeId_t Shop3PetriNetReasoning::open_fun316() {
    //add your code
    return -1;
}

void Shop3PetriNetReasoning::registerNodes() {
    //registration
    registerNode(341, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return addCustomerToLine_fun2_fun341(pSender, pReceiver, pExecTime, state);
    });
    registerNode(338, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return addCustomerToLine_fun1_fun338(pSender, pReceiver, pExecTime, state);
    });
    registerNode(333, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return Condition_cond333(pSender, pReceiver, pExecTime, state);
    });
    registerNode(330, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return removeCustomer_fun1_fun330(pSender, pReceiver, pExecTime, state);
    });
    registerNode(325, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return Condition_cond325(pSender, pReceiver, pExecTime, state);
    });
    registerNode(322, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return newCustomer_fun322(pSender, pReceiver, pExecTime, state);
    });
    registerNode(319, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return close_fun319(pSender, pReceiver, pExecTime, state);
    });
    registerNode(316, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
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