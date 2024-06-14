#include "agentGenerator.h"

AgentGenerator::AgentGenerator() {
    // Open the JSON file containing resource data
    // Read the content of the header file
    // Store the content of the header file in the resources map
    // Read the content of the source file (cpp file)
    // Store the content of the source file in the resources map

    //reactive
    resources[REACTIVE][TEMPLATE] = readJson(RESOURCE_REACTIVE_PATH, TEMPLATE_REACTIVE_JSON);
    resources[REACTIVE][FILE_H] = readFile(RESOURCE_REACTIVE_PATH, CLASS_REACTIVE_H);
    resources[REACTIVE][FILE_CPP] = readFile(RESOURCE_REACTIVE_PATH, CLASS_REACTIVE_CPP);

    //petri net
    resources[PETRI_NET][TEMPLATE] = readJson(RESOURCE_PETRINET_PATH, TEMPLATE_PETRINET_JSON);
    resources[PETRI_NET][FILE_H] = readFile(RESOURCE_PETRINET_PATH, CLASS_PETRINET_H);
    resources[PETRI_NET][FILE_CPP] = readFile(RESOURCE_PETRINET_PATH, CLASS_PETRINET_CPP);
}

void AgentGenerator::processJson(json data) {
    // Extract relevant JSON objects
    json source = data[DATA];
    json hierarchy = data[HIERARCHY];

    // Initialize the starting ID for agents
    AgentId_t agentId = REASONING_ID_START;

    // Iterate through each agent in the source data
    for (auto& [key, value] : source.items()) {
        // Map the node ID to the corresponding agent ID
        node2Agent[std::stoi(key)] = agentId;

        // Process the agent based on its type
        if (value.contains(REACTIVE)) {
            // Process a reactive agent
            processReactive(value[REACTIVE], agentId);
        }
        if (value.contains(PETRI_NET)) {
            processPetriNet(value[PETRI_NET], agentId);
        }

        // Increment the agent ID for the next agent
        agentId++;
    }
}

void AgentGenerator::processReactive(json data, AgentId_t agentId) {
    // Deep copy the template files
    std::string agent_h = fmt::format(resources[REACTIVE][FILE_H], agentId);
    std::string agent_cpp = fmt::format(resources[REACTIVE][FILE_CPP], agentId, agentId);

    // Initialize positions for insertion points
    size_t posAtr, posFun, posReg, posDef;

    // Loop over attributes
    posAtr = agent_h.find(SEARCH_ATR);
    for (std::string atrId : data[ATTRIBUTES]) {
        // Retrieve attribute data
        json atr = data[atrId];
        // Generate values to insert for attributes
        std::string valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_ATTRIBUTE], atr[TYPE_ATR], atr[NAME], atr[INIT_VALUE]);
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
            std::string valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_FUNCTION_DEF], funct[NAME]);
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

    // Save modified files
    std::string fileName = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_REACTIVE_FILE_NAME], agentId);
    saveFile(RESOURCE_REACTIVE_PATH, fileName + ".h", agent_h);
    saveFile(RESOURCE_REACTIVE_PATH, fileName + ".cpp", agent_cpp);
}

std::string AgentGenerator::readFile(std::string path, std::string name) {
    // Concatenate the path and name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, name);

    // Open the file
    std::ifstream fileSource(fullName);

    // Check if the file is successfully opened
    if (!fileSource.is_open()) {
        // Throw a runtime error if the file cannot be opened
        throw std::runtime_error(fmt::format("Error: Unable to open file {}.", fullName));
    }

    // Read the content of the file into a string
    std::string file_str((std::istreambuf_iterator<char>(fileSource)), std::istreambuf_iterator<char>());

    // Close the file
    fileSource.close();

    // Return the file content as a string
    return file_str;
}

json AgentGenerator::readJson(std::string path, std::string name) {
    // Concatenate the path and name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, name);

    // Open the JSON file
    std::ifstream fileSource(fullName);

    // Check if the file is successfully opened
    if (!fileSource.is_open()) {
        // Throw a runtime error if the file cannot be opened
        throw std::runtime_error(fmt::format("Error: Unable to open file {}.", fullName));
    }

    // JSON object to store the parsed data
    json source_json;

    // Parse the JSON file and store the data in the JSON object
    fileSource >> source_json;

    // Close the file
    fileSource.close();

    // Return the parsed JSON object
    return source_json;
}

void AgentGenerator::saveFile(std::string path, std::string fileName, std::string data) {
    // Concatenate the path and file name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, fileName);

    // Create an ofstream object
    std::ofstream outfile;

    // Open the file (this will create the file if it doesn't exist)
    outfile.open(fullName);

    // Check if the file is successfully opened
    if (!outfile.is_open()) {
        // Throw a runtime error if the file cannot be opened
        throw std::runtime_error(fmt::format("Error: Unable to open file {}.", fullName));
    }

    // Write data to the file
    outfile << data;

    // Close the file
    outfile.close();
}

void AgentGenerator::processPetriNet(json data, int agentId) {
    //empty
}
