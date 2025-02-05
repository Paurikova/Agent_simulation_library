#include "bird.h"

NodeId_t Bird::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    sendMessage(1,  pExecTime, pReceiver, pSender, -1, std::unordered_map<std::string, variant_t>{
            {"x", x},
            {"y", y},
            {"velX", velX},
            {"velY", velY}
    });
    return -1;
}

NodeId_t Bird::setPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args) {
    auto it = args.find("velX");
    velX = std::get<int>(it->second);
    it = args.find("velY");
    velY = std::get<int>(it->second);
    it = args.find("x");
    x = std::get<int>(it->second);
    it = args.find("y");
    y = std::get<int>(it->second);

    shape.setPosition(x, y); // Update bird shape position
}

void Bird::registerServices() {
    registerService(1, 1);
    registerService(2, 2);
}

void Bird::registerNodes() {
    registerNode(1, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args)->NodeId_t {
        return getPosition(pSender, pReceiver, pExecTime, args);
    });
    registerNode(2, [this](int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, variant_t> args)->NodeId_t {
        return setPosition(pSender, pReceiver, pExecTime, args);
    });
};