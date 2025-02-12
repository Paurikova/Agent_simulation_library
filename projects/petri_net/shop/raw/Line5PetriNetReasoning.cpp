//TODO incluce
#include "Line5PetriNetReasoning.h"
NodeId_t Line5PetriNetReasoning::hasCustomer_fun1_fun363(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::Condition_cond358(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 363;
    } else {
        //add your code
        return -1;
    }
}
NodeId_t Line5PetriNetReasoning::removeFromShop_fun355(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::removeFromLine_fun352(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::addToLine_fun1_fun349(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::Condition_cond344(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 349;
    } else {
        //add your code
        return -1;
    }
}

void Line5PetriNetReasoning::registerNodes() {
    //registration
    registerNode(363, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return hasCustomer_fun1_fun363(pSender, pReceiver, pExecTime, state);
    });
    registerNode(358, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return Condition_cond358(pSender, pReceiver, pExecTime, state);
    });
    registerNode(355, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return removeFromShop_fun355(pSender, pReceiver, pExecTime, state);
    });
    registerNode(352, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return removeFromLine_fun352(pSender, pReceiver, pExecTime, state);
    });
    registerNode(349, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
        return addToLine_fun1_fun349(pSender, pReceiver, pExecTime, state);
    });
    registerNode(344, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state))->NodeId_t{
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