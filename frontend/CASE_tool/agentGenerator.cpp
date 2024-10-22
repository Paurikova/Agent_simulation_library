#include "agentGenerator.h"

AgentGenerator::AgentGenerator() {
    // Open the JSON file containing resource data
    // Read the content of the header file
    // Store the content of the header file in the resources map
    // Read the content of the source file (cpp file)
    // Store the content of the source file in the resources map

    fileManager = std::make_unique<FileManager>();
    //reactive
    resources[REACTIVE][TEMPLATE] = fileManager->readJson(RESOURCE_REACTIVE_PATH, TEMPLATE_REACTIVE_JSON);
    resources[REACTIVE][FILE_H] = fileManager->readFile(RESOURCE_REACTIVE_PATH, CLASS_REACTIVE_H);
    resources[REACTIVE][FILE_CPP] = fileManager->readFile(RESOURCE_REACTIVE_PATH, CLASS_REACTIVE_CPP);

    //petri net
    resources[PETRI_NET][TEMPLATE] = fileManager->readJson(RESOURCE_PETRINET_PATH, TEMPLATE_PETRINET_JSON);
    resources[PETRI_NET][FILE_H] = fileManager->readFile(RESOURCE_PETRINET_PATH, CLASS_PETRINET_H);
    resources[PETRI_NET][FILE_CPP] = fileManager->readFile(RESOURCE_PETRINET_PATH, CLASS_PETRINET_CPP);

    //main
    resources[MAIN][TEMPLATE] = fileManager->readJson(RESOURCE_MAIN_PATH, TEMPLATE_MAIN_JSON);
}

void AgentGenerator::processJson(json data, std::string path) {
    // Extract relevant JSON objects
    json source = data[DATA];
    json hierarchy = data[HIERARCHY];

    // Initialize the starting ID for agents
    AgentId_t agentId;
    // Iterate through each agent in the source data
    for (auto& [key, value] : source.items()) {
        agentId = value[AGENT_ID];
        // Map the node ID to the corresponding agent ID
        node2Agent[std::stoi(key)] = agentId;

        // Process the agent based on its type
        if (value.contains(REACTIVE)) {
            // Process a reactive agent
            processReactive(value[REACTIVE], path, agentId);
        }
        if (value.contains(PETRI_NET)) {
            processPetriNet(value[PETRI_NET], path, agentId);
        }
    }
}

void AgentGenerator::processReactive(json data, std::string path, AgentId_t agentId) {
    // Deep copy the template files
    std::string agent_h = fmt::format(resources[REACTIVE][FILE_H], agentId);
    std::string agent_cpp = fmt::format(resources[REACTIVE][FILE_CPP], agentId, agentId);

    // Initialize positions for insertion points
    size_t posAtr, posFun, posReg, posDef, posOver;
    std::string valuesToInsert;

    // Loop over attributes
    posAtr = agent_h.find(SEARCH_ATR);
    for (std::string atrId : data[ATTRIBUTES]) {
        // Retrieve attribute data
        json atr = data[atrId];
        // Generate values to insert for attributes
        valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_ATTRIBUTE], atr[TYPE_ATR], atr[NAME], atr[INIT_VALUE]);
        // Insert values into the header file
        agent_h.insert(posAtr + SEARCH_ATR.length(), valuesToInsert);
    }

    // Loop over services
    posFun = agent_h.find(SEARCH_FUNCT);
    posDef = agent_cpp.find(SEARCH_H);
    for (std::string serviceId : data[SERVICES]) {
        // Retrieve service data
        json service = data[serviceId];
        // Skip empty linked functions
        if (service[LINKED].empty())
            continue;
        // Loop over linked functions
        for (std::string linked : service[LINKED]) {
            // Retrieve function data
            json funct = data[linked];
            // Generate values to insert for function definition
            valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_FUNCTION_DEF], funct[NAME]);
            // Insert function definition into the header file
            agent_h.insert(posFun + SEARCH_FUNCT.length(), valuesToInsert);
            // Generate values to insert for function implementation
            valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_FUNCTION_IMPL], agentId, funct[NAME]);
            // Insert function implementation into the source file
            agent_cpp.insert(posDef + SEARCH_H.length(), valuesToInsert);
            // Find registration position in the source file
            posReg = agent_cpp.find(SEARCH_FUNCT);
            // Generate values to insert for function registration
            valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_FUNCTION_REG], service[SERVICE], funct[NAME]);
            // Insert function registration into the source file
            agent_cpp.insert(posReg + SEARCH_FUNCT.length(), valuesToInsert);
        }
    }

    // Insert initial message definition if the agent ID is 1 (manager)
    if (agentId == MANAGER_ID) {
        posOver = agent_h.find(SEARCH_OVERRIDE);
        agent_h.insert(posOver + SEARCH_OVERRIDE.length(), resources[MAIN][TEMPLATE][TEMP_MAIN_INITMSG_DEF]);
        // Generate values to insert for function registration
        valuesToInsert = fmt::format(resources[MAIN][TEMPLATE][TEMP_MAIN_INITMSG_IMPL], agentId, "ReactiveReasoning");
        agent_cpp.insert(posDef + SEARCH_H.length(), valuesToInsert);
    }

    // Save modified files
    std::string fileName = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_REACTIVE_FILE_NAME], agentId);
    fileManager->saveFile(path, fileName + ".h", agent_h);
    fileManager->saveFile(RESOURCE_REACTIVE_PATH, fileName + ".cpp", agent_cpp);
}


void AgentGenerator::processPetriNet(json data, std::string path, int agentId) {
    // Deep copy the template files
    std::string agent_h = fmt::format(resources[PETRI_NET][FILE_H], agentId);
    std::string agent_cpp = fmt::format(resources[PETRI_NET][FILE_CPP], agentId, agentId);
}

void AgentGenerator::processMain(json data) {

}
