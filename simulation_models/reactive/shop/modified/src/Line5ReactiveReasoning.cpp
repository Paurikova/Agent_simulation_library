//TODO include
#include "../include/Line5ReactiveReasoning.h"
#include "../include/state_line.h"
std::queue<SimTime_t>& Line5ReactiveReasoning::chooseLine() {
    if (stateShop->custInLine0.size() <= stateShop->custInLine1.size()) {
        return stateShop->custInLine0;  // Line 0 is chosen
    } else {
        return stateShop->custInLine1;  // Line 1 is chosen
    }
}
void Line5ReactiveReasoning::removeFromLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: removeFromLine (line: {})", pReceiver, stateLine->line));

    auto& line = (stateLine->line == 0) ? stateShop->custInLine0 : stateShop->custInLine1;

    if (!line.empty()) {
        SimTime_t enterTime = line.front();
        line.pop();

        float timeInLine = pExecTime - enterTime;
        if (stateLine->line == 0) {
            stateShop->totalCustTimeInLine0 += timeInLine;
            stateShop->totalCustInLine0++;
        } else {
            stateShop->totalCustTimeInLine1 += timeInLine;
            stateShop->totalCustInLine1++;
        }
        logger->log(fmt::format("  [Line{} size: {}]\n", stateLine->line, line.size()));
        sendMessage(2, pExecTime, pReceiver, pSender, -1, stateLine);
    } else {
        logger->log("  Line is empty.\n");
    }
}

void Line5ReactiveReasoning::addToLine(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    auto& line = chooseLine();  // Get the appropriate line

    logger->log(fmt::format("{}: addToLine (chosen line: {})", pReceiver, (line == stateShop->custInLine0) ? 0 : 1));

    line.push(pExecTime);

    logger->log(fmt::format("  [Line{} size: {}]\n", (line == stateShop->custInLine0) ? 0 : 1, line.size()));

    if (line.size() == 1) {
        StateLine* stateLine = new StateLine(line == stateShop->custInLine0 ? 0 : 1);
        sendMessage(1, pExecTime, pReceiver, pReceiver+1, -1, stateLine);  // Notify cash (example for line 0)
    }
}

void Line5ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        removeFromLine(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        addToLine(pSender, pReceiver, pExecTime, state);
    });
}