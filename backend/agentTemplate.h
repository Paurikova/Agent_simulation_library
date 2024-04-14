#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <fmt/format.h>

class AgentTemplate {
private:
    std::unique_ptr<std::vector<std::pair<std::string, std::string>>> attributes;
    std::unique_ptr<std::vector<std::pair<int, std::string>>> functions;
public:
    explicit AgentTemplate();
    void addAttributes(std::string pType, std::string pName);
    void addFunction(int pServiceId, std::string pName);
    int getAttributesSize();
    int getFunctionSize();
    std::pair<std::string, std::string> getAttribute(int pPos);
    std::pair<int, std::string> getFunction(int pPos);
};