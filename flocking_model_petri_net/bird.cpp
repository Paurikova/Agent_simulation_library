#include "bird.h"

NodeId_t Bird::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: getPosition\n", pReceiver));
    sendMessage(1,  pExecTime, pReceiver, pSender, -1, std::unordered_map<std::string, variant_t>{
            {"x", x},
            {"y", y},
            {"velX", velX},
            {"velY", velY}
    });
}

NodeId_t Bird::setPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: setPosition\n", pReceiver));

    auto it = args.find("x");
    x = std::get<float>(it->second);
    it = args.find("y");
    y = std::get<float>(it->second);
    it = args.find("velX");
    velX = std::get<float>(it->second);
    it = args.find("velY");
    velY = std::get<float>(it->second);
    shape.setPosition(x, y); // Update bird shape position

    sendMessage(7, pExecTime, pReceiver, pSender);
}

NodeId_t Bird::move(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    sendMessage(5, pExecTime, pReceiver, pSender);
}

NodeId_t Bird::draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state) {
    logger->log(fmt::format("{}: draw\n", pReceiver));
    window.draw(shape);
    sendMessage(6, pExecTime, pReceiver, pSender);
}

void Bird::registerFunctions() {
    registerFunction(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return getPosition(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return setPosition(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(3, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return move(pSender, pReceiver, pExecTime, args);
    });
    registerFunction(4, [this](int pSender, int pReceiver, SimTime_t pExecTime, State* state)->NodeId_t {
        return draw(pSender, pReceiver, pExecTime, args);
    });
}