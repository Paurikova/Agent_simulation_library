//TODO include
#include "../include/Line5PetriNetReasoning.h"
#include "../include/state_line.h"
std::queue<SimTime_t>& Line5PetriNetReasoning::chooseLine() {
    if (stateShop->custInLine0.size() <= stateShop->custInLine1.size()) {
        return stateShop->custInLine0;  // Line 0 is chosen
    } else {
        return stateShop->custInLine1;  // Line 1 is chosen
    }
}

NodeId_t Line5PetriNetReasoning::removeFromLine_fun234(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::Code_code230(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return 234;
}
NodeId_t Line5PetriNetReasoning::Code_code226(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    stateShop->totalCustTimeInLine0 += timeInLine;
    stateShop->totalCustInLine0++;
    return 234;
}
NodeId_t Line5PetriNetReasoning::removeFromLine_fun2_fun238(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    return -1;
}
NodeId_t Line5PetriNetReasoning::removeFromLine_cond221(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromLine_cond221 (line: {})", pReceiver, stateLine->line));
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    auto& line = (stateLine->line == 0) ? stateShop->custInLine0 : stateShop->custInLine1;
    SimTime_t enterTime = line.front();
    line.pop();
    float timeInLine = pExecTime - enterTime;
    if (stateLine->line == 0) {
        //add your code
        return 226;
    } else {
        //add your code
        return 230;
    }
}
NodeId_t Line5PetriNetReasoning::removeFromLine_cond216(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: removeFromLine_cond216 (line: {})", pReceiver, stateLine->line));

    auto& line = (stateLine->line == 0) ? stateShop->custInLine0 : stateShop->custInLine1;

    if (line.empty()) {
        //add your code
        return 221;
    } else {
        //add your code
        return 238;
    }
}

NodeId_t Line5PetriNetReasoning::addToLine_fun216(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    auto& line = chooseLine();  // Get the appropriate line

    logger->log(fmt::format("{}: addToLine_fun216 (chosen line: {})", pReceiver, (line == stateShop->custInLine0) ? 0 : 1));

    line.push(pExecTime);

    logger->log(fmt::format("  [Line{} size: {}]\n", (line == stateShop->custInLine0) ? 0 : 1, line.size()));

    if (line.size() == 1) {
        StateLine* stateLine = new StateLine(line == stateShop->custInLine0 ? 0 : 1);
        sendMessage(1, pExecTime, pReceiver, pReceiver+1, -1, stateLine);  // Notify cash (example for line 0)
    }
    return -1;
}

void Line5PetriNetReasoning::registerNodes() {
    //registration
    registerNode(234, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return removeFromLine_fun234(pSender, pReceiver, pExecTime, state);
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
        return addToLine(pSender, pReceiver, pExecTime, state);
    });
    registerNode(213, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return addToLine_fun213(pSender, pReceiver, pExecTime, state);
    });

    registerNode(205, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t{
        return Condition_cond205(pSender, pReceiver, pExecTime, state);
    });
}

void Line5PetriNetReasoning::registerServices() {
    //services
    registerService(1, 216);
    registerService(2, 205);
}