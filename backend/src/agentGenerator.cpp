#include "../include/agentGenerator.h"

AgentId_t AgentGenerator::nextAgentId = AGENT_ID_START;

AgentGenerator::AgentGenerator() {
    outputJson = {
            {"h", nlohmann::json::array()},
            {"cpp", nlohmann::json::array()}
    };
    // Open the JSON file
    std::ifstream file(fmt::format("{}/{}}", RESOURCE_PATH, TEMPLATE_JSON));

    // Check if the file is open
    if (file.is_open()) {
        // Parse the JSON file and store the data in the JSON object
        file >> resources;

        // Close the file
        file.close();
    } else {
        std::cerr << fmt::format("Failed to open file {}!", TEMPLATE_JSON) << std::endl;
    }
}

void AgentGenerator::createAgent(AgentTemplate* agentTemplate) {
    //find position of private part of agent body definition
    AgentId_t nextId = nextAgentId++;
    std::string agentH = fmt::format(resources.at("AgentH"), nextId);
    std::string attributeTemp = resources.at("Attribute");
    std::string functionDefTemp = resources.at("FunctionDef");
    std::string agentCpp = fmt::format(resources.at("AgentCpp"), nextId, nextId);
    std::string functionFunctionImpl = fmt::format(resources.at("FunctionImpl"), nextId);
    std::string functionFunctionReg = resources.at("FunctionReg");
    //find right place for additing attributes' and functions' definitions
    size_t pos = agentH.find_last_of("private:");
    //add attributes
    int atrributesSize = agentTemplate->getAttributesSize();
    for (int i = 0; i < atrributesSize; i++) {
        std::pair<std::string , std::string> attribute = agentTemplate->getAttribute(i);
        std::string insertedString = fmt::format("\n    " + attributeTemp, attribute.first, attribute.second);
        agentH.insert(pos, insertedString);
        pos += insertedString.length();
    }
    //add functions
    int functionsSize = agentTemplate->getFunctionSize();
    for (int i = 0; i < functionsSize; i++) {
        std::pair<int , std::string> functionName = agentTemplate->getFunction(i);
        std::string insertedString = fmt::format("\n    " + functionDefTemp, functionName.second);
        agentH.insert(pos, insertedString);
        pos += insertedString.length();
    }

    outputJson["h"].push_back({fmt::format("Agent{}", nextId), agentH});

    //create cpp file
    size_t posReg = agentH.find_last_of("{{");
    size_t posImpl = agentH.find_last_of("}}");
    for (int i = 0; i < functionsSize; i++) {
        std::pair<int , std::string> functionName = agentTemplate->getFunction(i);
        std::string insertedString = fmt::format("\n    " + functionFunctionReg, functionName.first, functionName.second);
        agentCpp.insert(posReg, insertedString);
        posReg += insertedString.length();
        insertedString = fmt::format("\n    " + functionFunctionImpl, functionName.first);
        agentCpp.insert(posImpl, insertedString);
        posImpl += insertedString.length();
    }

   //add agent to json obj
    outputJson["cpp"].push_back({fmt::format("Agent{}", nextId), agentCpp});
}

void AgentGenerator::generateJson() {
    std::ofstream output(fmt::format("{}/{}", RESOURCE_PATH, OUTPUT_FILE));
    if (output.is_open()) {
        output << outputJson;
        output.close();
    } else {
        std::cerr << fmt::format("Failed to open file {}!", OUTPUT_FILE) << std::endl;;
    }
}
