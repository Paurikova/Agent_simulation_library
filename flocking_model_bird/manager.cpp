#include "manager.h"

void Manager::initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: update_positions\n", pReceiver));
    StateBird* stateBird = dynamic_cast<StateBird*>(state);
    birds[pSender - 2] = stateBird;
    if (pSender < number_of_birds + 1) {
        pSender += 1;
        sendMessage(1, pExecTime, pReceiver, pSender);
        return;
    }
    sendMessage(2, pExecTime, pReceiver, pReceiver);
}

void Manager::isWindowOpen(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: isWindowOpen\n", pReceiver));
    if (window.isOpen()) {
        sendMessage(2, pExecTime, pSender, 2);
    }
}

void Manager::handleEvents(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: handle_events\n", pReceiver));
    // Handle events
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    sendMessage(2, pExecTime, pReceiver, 2);
}

void Manager::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: getPosition\n", pReceiver));
    StateNeighbor* stateNeighbor = dynamic_cast<StateNeighbor*>(state);
    sendMessage(2,  pExecTime, pReceiver, pSender, -1, birds[stateNeighbor->neighbor]);
}

void Manager::clearScreen(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: clearScreen\n", pReceiver));
    // Clear the screen
    window.clear(sf::Color::Black);
    for (int i = 0; i < number_of_birds; i++) {
        sendMessage(5, pExecTime, pReceiver, i + 2);
    }
}

void Manager::display(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: display\n", pReceiver));
    if (pSender - 1 == number_of_birds) {
        // Display everything on the screen
        window.display();
        //Do run again
        sendMessage(1, pExecTime + 1, pReceiver, 2);
    }
}

void Manager::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return initialization(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return isWindowOpen(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return handleEvents(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return clearScreen(pSender, pReceiver, pExecTime, state);
    });
    registerFunction(5, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
        return display(pSender, pReceiver, pExecTime, state);
    });

};

void Manager::initMessage() {
    // Add implementation of initial message
    // Replace:
    //      pServiceId by required service ID
    //      pExecTime by execution time of event
    //      pReceiver by the ID of the receiving agent
    //open
    sendMessage(1, 0, 1, 2);
}
