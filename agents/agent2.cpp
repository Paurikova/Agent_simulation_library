//
// Created by miska on 10.3.2024.
//

#include "agent2.h"

void Agent2::registerFunctions() {
    registerFunction(1, [this](int sender) {
        writeGoodbye(sender);
    });
    registerFunction(2, [this](int sender) {
        allDone(sender);
    });
}

//functions
void Agent2::writeGoodbye(int sender) {
    std::cout << "Goodbye." << std::endl;
    sendMessage(1,1,getCurrTime());
}

void Agent2::allDone(int sender) {
    std::cout << "Done Agent2." << std::endl;
}
