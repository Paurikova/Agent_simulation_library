//TODO include
#include "Cash6PetriNetReasoning.h"
NodeId_t Cash6PetriNetReasoning::endCustomer_fun1_fun321(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Code_code316(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 321;
}
NodeId_t Cash6PetriNetReasoning::Code_code313(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 321;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond308(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 313;
    } else {
        //add your code
        return 316;
    }
}
NodeId_t Cash6PetriNetReasoning::processCustomer_fun2_fun305(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::processCustomer_fun1_fun302(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond296(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 302;
    } else {
        //add your code
        return 305;
    }
}
NodeId_t Cash6PetriNetReasoning::Code_code292(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 296;
}
NodeId_t Cash6PetriNetReasoning::Code_code288(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 296;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond283(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 288;
    } else {
        //add your code
        return 292;
    }
}
NodeId_t Cash6PetriNetReasoning::acceptCustomer_fun2_fun280(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::scceptCustomer_fun1_fun277(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond272(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    if () {
        //add your code
        return 277;
    } else {
        //add your code
        return 280;
    }
}

void Cash6PetriNetReasoning::registerNodes() {
    //registration
    registerNode(321, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return endCustomer_fun1_fun321(pSender, pReceiver, pExecTime, state);
    });
    registerNode(316, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code316(pSender, pReceiver, pExecTime, state);
    });
    registerNode(313, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code313(pSender, pReceiver, pExecTime, state);
    });
    registerNode(308, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond308(pSender, pReceiver, pExecTime, state);
    });
    registerNode(305, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return processCustomer_fun2_fun305(pSender, pReceiver, pExecTime, state);
    });
    registerNode(302, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return processCustomer_fun1_fun302(pSender, pReceiver, pExecTime, state);
    });
    registerNode(296, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond296(pSender, pReceiver, pExecTime, state);
    });
    registerNode(292, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code292(pSender, pReceiver, pExecTime, state);
    });
    registerNode(288, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code288(pSender, pReceiver, pExecTime, state);
    });
    registerNode(283, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond283(pSender, pReceiver, pExecTime, state);
    });
    registerNode(280, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return acceptCustomer_fun2_fun280(pSender, pReceiver, pExecTime, state);
    });
    registerNode(277, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return scceptCustomer_fun1_fun277(pSender, pReceiver, pExecTime, state);
    });
    registerNode(272, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond272(pSender, pReceiver, pExecTime, state);
    });
}

void Cash6PetriNetReasoning::registerServices() {
    //services
    registerService(3, 308);
    registerService(2, 283);
    registerService(1, 272);
}