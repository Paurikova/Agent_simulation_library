#include "../include/Cash6ReactiveReasoning.h"
#include "../include/state_line.h"
void Cash6ReactiveReasoning::endCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: endCustomer (Line {})\n", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        hasCustom1 = false;
    } else {
        hasCustom2 = false;
    }
    sendMessage(4, pExecTime, pReceiver, 3, -1, stateLine);
}
void Cash6ReactiveReasoning::processCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine* stateLine = dynamic_cast<StateLine*>(state);
    logger->log(fmt::format("{}: processCustomer (Line {})", pReceiver, stateLine->line));
    if (stateLine->line == 0) {
        hasCustom1 = true;
    } else {
        hasCustom2 = true;
    }

    // Process the customer
    logger->log(fmt::format("  [{}]\n", stateLine->line == 0 ? processLength1 : processLength2));
    sendMessage(3, pExecTime + (stateLine->line == 0 ? processLength1 : processLength2), pReceiver, pReceiver, -1, stateLine);
}

void Cash6ReactiveReasoning::acceptCustomer(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    StateLine *stateLine = dynamic_cast<StateLine *>(state);
    logger->log(fmt::format("{}: acceptCustomer (Line {})\n", pReceiver, stateLine->line));

    std::queue<float> &line = (stateLine->line == 0) ? stateShop->custInLine0 : stateShop->custInLine1;

    if (!(stateLine->line == 0 ? hasCustom1 : hasCustom2)) {
        sendMessage(2, pExecTime, pReceiver, 4, -1, stateLine);  // Customer accepted by cash
        return;
    }
    delete state;
}

void Cash6ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        endCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        processCustomer(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        acceptCustomer(pSender, pReceiver, pExecTime, state);
    });
}
