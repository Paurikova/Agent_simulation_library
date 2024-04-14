#pragma once


#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fmt/format.h>

#include "agentTemplate.h"
#include "../library/include/types.h"

class AgentGenerator {
private:
    const std::string TEMPLATE_JSON = "templates.json";
    const std::string OUTPUT_FILE = "output.json";
    const std::string RESOURCE_PATH = "/resource";
    static AgentId_t nextAgentId;
    nlohmann::json outputJson;
    nlohmann::json resources;
public:
    AgentGenerator();
    void createAgent(AgentTemplate* agentTemplate);
    void generateJson();
};