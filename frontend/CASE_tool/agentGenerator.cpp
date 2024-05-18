#include "agentGenerator.h"

AgentGenerator::AgentGenerator() {
    // Open the JSON file containing resource data
    resources = readJson(RESOURCE_PATH, TEMPLATE_JSON);

    // Read the content of the header file
    std::string fileH = readFile(RESOURCE_PATH, CLASS_H);

    // Store the content of the header file in the resources map
    resources[FILE_H] = fileH;

    // Read the content of the source file (cpp file)
    std::string fileCpp = readFile(RESOURCE_PATH, CLASS_CPP);

    // Store the content of the source file in the resources map
    resources[FILE_CPP] = fileCpp;
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
            // PETRI_NET handling not implemented yet
            // Add implementation if needed in the future
        }

        // Increment the agent ID for the next agent
        agentId++;
    }
}

void AgentGenerator::processReactive(json data, AgentId_t agentId) {
    // Deep copy the template files
    std::string agent_h = fmt::format(resources[FILE_H], agentId);
    std::string agent_cpp = fmt::format(resources[FILE_CPP], agentId, agentId);

    // Initialize positions for insertion points
    size_t posAtr, posFun, posReg, posDef;

    // Loop over attributes
    posAtr = agent_h.find(SEARCH_ATR);
    for (std::string atrId : data[ATTRIBUTES]) {
        // Retrieve attribute data
        json atr = data[atrId];
        // Generate values to insert for attributes
        std::string valuesToInsert = fmt::format(resources[TEMP_ATTRIBUTE], atr[TYPE_ATR], atr[NAME], atr[INIT_VALUE]);
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
            std::string valuesToInsert = fmt::format(resources[TEMP_FUNCTION_DEF], funct[NAME]);
            // Insert function definition into the header file
            agent_h.insert(posFun + SEARCH_FUNCT.length(), valuesToInsert);
            // Generate values to insert for function implementation
            valuesToInsert = fmt::format(resources[TEMP_FUNCTION_IMPL], agentId, funct[NAME]);
            // Insert function implementation into the source file
            agent_cpp.insert(posDef + SEARCH_H.length(), valuesToInsert);
            // Find registration position in the source file
            posReg = agent_cpp.find(SEARCH_FUNCT);
            // Generate values to insert for function registration
            valuesToInsert = fmt::format(resources[TEMP_FUNCTION_REG], service[SERVICE], funct[NAME]);
            // Insert function registration into the source file
            agent_cpp.insert(posReg + SEARCH_FUNCT.length(), valuesToInsert);
        }
    }

    // Save modified files
    std::string fileName = fmt::format(resources[TEMP_REACTIVE_FILE_NAME], agentId);
    saveFile(RESOURCE_PATH, fileName + ".h", agent_h);
    saveFile(RESOURCE_PATH, fileName + ".cpp", agent_cpp);
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