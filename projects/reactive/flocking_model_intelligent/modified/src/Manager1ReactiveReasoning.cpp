//TODO incluce
#include "../include/Manager1ReactiveReasoning.h"
void Manager1ReactiveReasoning::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    for (int i = 0; i < number_of_birds; i++) {
        sendMessage(2, 0, 1, i+2);
    }
}

Manager1ReactiveReasoning::~Manager1ReactiveReasoning() {
    for(int i = 0; i < birds.size(); i++) {
        delete birds[i];
    }
    birds.clear();
}

void Manager1ReactiveReasoning::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: draw\n", pReceiver));
    // Clear the screen
    window.clear(sf::Color::Black);
    for (int i = 0; i < number_of_birds; i++) {
        shape.setPosition(birds[i]->x, birds[i]->y);
        window.draw(shape);
    }
    // Display everything on the screen
    window.display();
    //Do run again
    sendMessage(2, pExecTime + 1, pReceiver, pReceiver);
}
void Manager1ReactiveReasoning::startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: isWindowOpen\n", pReceiver));
    if (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sendMessage(3, pExecTime, pReceiver, 2);
    }
}
void Manager1ReactiveReasoning::initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    //add your code
    logger->log(fmt::format("{}: initialization\n", pReceiver));
    StateBird* stateBird = dynamic_cast<StateBird*>(state);
    birds[pSender - 2] = stateBird;
    if (pSender < number_of_birds + 1) {
        return;
    }
    sendMessage(2, pExecTime, pReceiver, pReceiver);
}

void Manager1ReactiveReasoning::registerFunctions() {
    //registration
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        draw(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        startWindow(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        initialization(pSender, pReceiver, pExecTime, state);
    });
}