#include "bird.h"

NodeId_t Bird::getPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
    sendMessage(1,  pExecTime, pReceiver, pSender, -1, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>>{
            {"x", x},
            {"y", y},
            {"velX", velX},
            {"velY", velY}
    });
    return -1;
}

NodeId_t Bird::setPosition(int pSender, int pReceiver, SimTime_t pExecTime, std::unordered_map<std::string, std::variant<int, float, std::string, std::vector<float>>> args) {
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