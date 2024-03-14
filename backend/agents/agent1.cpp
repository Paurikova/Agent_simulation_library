#include "agent1.h"

void Agent1::writeHello(int sender) {
    if (counter%3 == 0) {
        sendMessage(1,getCurrTime(),3);
        counter = 1;
    } else {
        std::cout << "Hello." << std::endl;
        counter++;
    }
}

void Agent1::allDone(int sender) {
    std::cout << "Done Agent1." << std::endl;
}

void Agent1::registerFunctions() {
    registerFunction(1, [this](int sender) {
        writeHello(sender);
    });
    registerFunction(2, [this](int sender) {
        allDone(sender);
    });
}
