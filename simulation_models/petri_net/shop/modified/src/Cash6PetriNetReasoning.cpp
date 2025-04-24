//TODO include
#include "../include/Cash6PetriNetReasoning.h"
#include "../include/state_line.h"
NodeId_t Cash6PetriNetReasoning::endCustomer_fun321(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_fun321 (Line {})\n", pReceiver, stateLine->line));
    sendMessage(4, pExecTime, pReceiver, 3, -1, state);
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Code_code316(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_Code_code316 (Line {})\n", pReceiver, stateLine->line));
    hasCustom2 = false;
    return 321;
}
NodeId_t Cash6PetriNetReasoning::Code_code313(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_Code_code313 (Line {})\n", pReceiver, stateLine->line));
    hasCustom1 = false;
    return 321;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond308(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer_Condition_cond308 (Line {})\n", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        //add your code
        return 313;
    } else {
        //add your code
        return 316;
    }
}
NodeId_t Cash6PetriNetReasoning::processCustomer_fun305(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer_fun305 (Line {})", pReceiver, stateLine->line));
    logger->log(fmt::format("  [{}]\n", processLength2));
    sendMessage(3, pExecTime + processLength2 , pReceiver, pReceiver, -1, state);
    return -1;
}
NodeId_t Cash6PetriNetReasoning::processCustomer_fun302(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer_fun302 (Line {})", pReceiver, stateLine->line));
    logger->log(fmt::format("  [{}]\n", processLength1));
    sendMessage(3, pExecTime + processLength1 , pReceiver, pReceiver, -1, state);
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond296(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer_Condition_cond296 (Line {})", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        //add your code
        return 302;
    } else {
        //add your code
        return 305;
    }
}
NodeId_t Cash6PetriNetReasoning::Code_code292(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: processCustomer_Code_code292 (Line {})\n", pReceiver, stateLine->line));
    hasCustom2 = true;
    return 296;
}
NodeId_t Cash6PetriNetReasoning::Code_code288(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: processCustomer_Code_code288 (Line {})\n", pReceiver, stateLine->line));
    hasCustom1 = true;
    return 296;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond283(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer (Line {})", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        //add your code
        return 288;
    } else {
        //add your code
        return 292;
    }
}
NodeId_t Cash6PetriNetReasoning::acceptCustomer_fun280(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer_fun280 (Line {})\n", pReceiver, stateLine->line));
    delete state;
    return -1;
}
NodeId_t Cash6PetriNetReasoning::acceptCustomer_fun277(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer_fun277 (Line {})\n", pReceiver, stateLine->line));
    sendMessage(2, pExecTime, pReceiver, 4, -1, stateLine);  // Customer accepted by cash
    return -1;
}
NodeId_t Cash6PetriNetReasoning::Condition_cond272(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer_Condition_cond272 (Line {})\n", pReceiver, stateLine->line));
    if (!(stateLine->line == 0 ? hasCustom1 : hasCustom2)) {
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
        return endCustomer_fun321(pSender, pReceiver, pExecTime, state);
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
        return processCustomer_fun305(pSender, pReceiver, pExecTime, state);
    });
    registerNode(302, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return processCustomer_fun302(pSender, pReceiver, pExecTime, state);
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
        return acceptCustomer_fun280(pSender, pReceiver, pExecTime, state);
    });
    registerNode(277, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return acceptCustomer_fun277(pSender, pReceiver, pExecTime, state);
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