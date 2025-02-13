#include "../include/bird.h"

void Bird::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: getPosition\n", pReceiver));
    sendMessage(1,  pExecTime, pReceiver, pSender, -1, birdState);
}

void Bird::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: move\n", pReceiver));
    sendMessage(3,  pExecTime, pReceiver, pSender);
}

void Bird::setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: setPosition\n", pReceiver));
    StateBird* inputState = dynamic_cast<StateBird*>(state);
    birdState->x = inputState->x;
    birdState->y = inputState->y;
    birdState->velX = inputState->velX;
    birdState->velY = inputState->velY;

    sendMessage(4, pExecTime, pReceiver, pSender);
}

void Bird::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return getPosition(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return move(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return setPosition(pSender, pReceiver, pExecTime, state);
    });
};