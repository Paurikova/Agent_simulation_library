#include "../include/agentTemplate.h"

AgentTemplate::AgentTemplate() {
    attributes = std::make_unique<std::vector<std::pair<std::string, std::string>>>();
    functions = std::make_unique<std::vector<std::pair<int, std::string>>>();
}

void AgentTemplate::addAttributes(std::string pType, std::string pName) {
    attributes->emplace_back(pType, pName);
}

void AgentTemplate::addFunction(int pServiceId, std::string pName) {
    functions->emplace_back(pServiceId, pName);
}

int AgentTemplate::getAttributesSize() {
    return attributes->size();
}

int AgentTemplate::getFunctionSize() {
    return functions->size();
}

std::pair<std::string, std::string> AgentTemplate::getAttribute(int pPos) {
    if (pPos >= attributes->size()) {
        throw std::runtime_error(fmt::format(
                "Requeested position {} is entered incorrectly. Current size of attributes is {}.", pPos,
                attributes->size()));
    }
    return attributes->at(pPos);
}

std::pair<int, std::string>AgentTemplate::getFunction(int pPos) {
    if (pPos >= functions->size()) {
        throw std::runtime_error(fmt::format(
                "Requeested position {} is entered incorrectly. Current size of functions is {}.", pPos,
                functions->size()));
    }
    return functions->at(pPos);
}