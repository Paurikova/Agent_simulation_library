//TODO incluce
#include "../include/Bird2ReactiveReasoning.h"
void Bird2ReactiveReasoning::setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: setPosition\n", pReceiver));
    StateBird* inputState = dynamic_cast<StateBird*>(state);
    birdState->x = inputState->x;
    birdState->y = inputState->y;
    birdState->velX = inputState->velX;
    birdState->velY = inputState->velY;

    sendMessage(4, pExecTime, pReceiver, pSender);
}
void Bird2ReactiveReasoning::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: move\n", pReceiver));
    sendMessage(3,  pExecTime, pReceiver, pSender);
}
void Bird2ReactiveReasoning::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: getPosition\n", pReceiver));
    sendMessage(1,  pExecTime, pReceiver, pSender, -1, birdState);
}


void Bird2ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        setPosition(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        move(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        getPosition(pSender, pReceiver, pExecTime, state);
    });
}