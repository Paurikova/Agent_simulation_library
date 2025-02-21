#include "../include/Cash6PetriNetReasoning.h"

NodeId_t Cash6PetriNetReasoning::endCustomer_fun389(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: endCustomer_fun389\n", pReceiver));
    hasCustom = false;
    sendMessage(3, pExecTime, pReceiver, pReceiver - 2);
    return -1;
}
NodeId_t Cash6PetriNetReasoning::processCustomer_fun386(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: processCustomer_fun386\n", pReceiver));
    hasCustom = true;
    //process customer
    logger->log(fmt::format("  [{}]\n" , processLength));
    sendMessage(3, pExecTime + processLength, pReceiver, pReceiver);
    return -1;
}
NodeId_t Cash6PetriNetReasoning::acceptCustomerFun2_fun383(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    delete state;
    //add your code
    logger->log(fmt::format("{}: acceptCustomerFun2_fun383", pReceiver));
    // The cash accept customer
    sendMessage(2, pExecTime, pReceiver, pSender);
    return -1;
}
NodeId_t Cash6PetriNetReasoning::acceptCustomer_fun1_fun380(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateBreak* cashBreak = dynamic_cast<StateBreak*>(state);
    logger->log(fmt::format("{}: acceptCustomer_fun1_fun380", pReceiver));
    //has break
    logger->log(fmt::format("       Break [{}] [{}]\n", pReceiver, cashBreak->cashBreak));
    //accept customer after break
    sendMessage(2, cashBreak->cashBreak + breakLength, pReceiver, pSender);
    delete state;
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond375(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: Condition_cond375\n", pReceiver));
    StateBreak* breakTime = dynamic_cast<StateBreak*>(state);
    if (breakTime->cashBreak > -1 ) {
        //add your code
        return 380;
    } else {
        //add your code
        return 383;
    }
}
NodeId_t Cash6PetriNetReasoning::Code_code371(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: Code_code371\n", pReceiver));
    //Has break?
    int breakTime = -1;
    // Loop through each row
    for (int j = 0; j < 2; ++j) {
        // Check if the current element is 200
        if (breaks[j] >= pExecTime && breaks[j] + breakLength <= pExecTime) {
            breakTime = breaks[j];
            break;
        }
    }
    StateBreak* stateBreak = dynamic_cast<StateBreak*>(state);
    stateBreak->cashBreak = breakTime;
    return 375;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond366(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: Condition_cond366\n", pReceiver));
    if (!hasCustom) {
        //add your code
        return 371;
    } else {
        //add your code
        delete state;
        return -1;
    }
}

void Cash6PetriNetReasoning::registerNodes() {
    //registration
    registerNode(389, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return endCustomer_fun389(pSender, pReceiver, pExecTime, state);
    });
    registerNode(386, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return processCustomer_fun386(pSender, pReceiver, pExecTime, state);
    });
    registerNode(383, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return acceptCustomerFun2_fun383(pSender, pReceiver, pExecTime, state);
    });
    registerNode(380, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return acceptCustomer_fun1_fun380(pSender, pReceiver, pExecTime, state);
    });
    registerNode(375, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond375(pSender, pReceiver, pExecTime, state);
    });
    registerNode(371, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Code_code371(pSender, pReceiver, pExecTime, state);
    });
    registerNode(366, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond366(pSender, pReceiver, pExecTime, state);
    });
}

void Cash6PetriNetReasoning::registerServices() {
    //services
    registerService(3, 389);
    registerService(2, 386);
    registerService(1, 366);
}