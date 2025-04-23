#include "../include/line.h"
#include "../include/state_line.h"

std::queue<SimTime_t>& Line::chooseLine() {
    if (stateShop->custInLine0.size() <= stateShop->custInLine1.size()) {
        return stateShop->custInLine0;  // Line 0 is chosen
    } else {
        return stateShop->custInLine1;  // Line 1 is chosen
    }
}

//1
NodeId_t Line::addToLine_cond1(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    auto& line = chooseLine();  // Get the appropriate line

    logger->log(fmt::format("{}: addToLine (chosen line: {})", pReceiver, (line == stateShop->custInLine0) ? 0 : 1));

    line.push(pExecTime);

    logger->log(fmt::format("  [Line{} size: {}]\n", (line == stateShop->custInLine0) ? 0 : 1, line.size()));

    if (line.size() == 1) {
        StateLine* stateLine = new StateLine(line == stateShop->custInLine0 ? 0 : 1);
        sendMessage(1, pExecTime, pReceiver, pReceiver+1, -1, stateLine);
        return -1;
    }
    return -1;
}

//2
NodeId_t Line::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: removeFromLine", pReceiver));
    stateShop->totalCustTimeInLine[pReceiver] += pExecTime - stateShop->custInLines[pReceiver].front();
    stateShop->totalCustInLine[pReceiver]++;
    stateShop->custInLines[pReceiver].pop();
    logger->log(fmt::format("  [{}]\n", stateShop->custInLines[pReceiver].size()));
    //process customer by cash
    sendMessage(2, pExecTime, pReceiver, pSender);
    return -1;
}

//5
void Line::registerNodes() {
    // Register a lambda function to handle function
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return addToLine_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerNode(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return removeFromShop(pSender, pReceiver, pExecTime, state);
    });
    registerNode(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return hasCustomer_cond1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return addToLine_fun1(pSender, pReceiver, pExecTime, state);
    });
    registerNode(6, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) -> NodeId_t {
        return hasCustomer_fun1(pSender, pReceiver, pExecTime, state);
    });
}

void Line::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
    registerService(3, 3);
    registerService(4, 4);
}
