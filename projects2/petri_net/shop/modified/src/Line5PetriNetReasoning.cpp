//TODO include
#include "../include/Line5PetriNetReasoning.h"
NodeId_t Line5PetriNetReasoning::removeFromLine_fun1_fun234(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::Code_code230(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 234;
}
NodeId_t Line5PetriNetReasoning::Code_code226(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 234;
}
NodeId_t Line5PetriNetReasoning::removeFromLine_fun2_fun238(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::Condition_cond221(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 226;
    } else {
        //add your code
        return 230;
    }
}
NodeId_t Line5PetriNetReasoning::Condition_cond216(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 221;
    } else {
        //add your code
        return 238;
    }
}
NodeId_t Line5PetriNetReasoning::addToLine_fun2_fun213(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::addToLine_fun1_fun210(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::Condition_cond205(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 210;
    } else {
        //add your code
        return 213;
    }
}

void Line5PetriNetReasoning::registerNodes() {
    //registration
    registerNode(234, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeFromLine_fun1_fun234(pSender, pReceiver, pExecTime, state);
    });
    registerNode(230, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code230(pSender, pReceiver, pExecTime, state);
    });
    registerNode(226, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code226(pSender, pReceiver, pExecTime, state);
    });
    registerNode(238, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeFromLine_fun2_fun238(pSender, pReceiver, pExecTime, state);
    });
    registerNode(221, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond221(pSender, pReceiver, pExecTime, state);
    });
    registerNode(216, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond216(pSender, pReceiver, pExecTime, state);
    });
    registerNode(213, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addToLine_fun2_fun213(pSender, pReceiver, pExecTime, state);
    });
    registerNode(210, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addToLine_fun1_fun210(pSender, pReceiver, pExecTime, state);
    });
    registerNode(205, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond205(pSender, pReceiver, pExecTime, state);
    });
}

void Line5PetriNetReasoning::registerServices() {
    //services
    registerService(2, 216);
    registerService(1, 205);
}