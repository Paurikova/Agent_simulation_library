#include "../include/agentGenerator.h"

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
        valuesToInsert = fmt::format(resources[MAIN][TEMPLATE][TEMP_ATTRIBUTE], atr[TYPE_ATR], atr[NAME], atr[INIT_VALUE]);
        // Insert values into the header file
        agent_h.insert(posAtr + SEARCH_ATR.length(), valuesToInsert);
    }

    // Loop over services
    posFun = agent_h.find(SEARCH_FUNCT);
    posDef = agent_cpp.find(SEARCH_REACTIVE_H);
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
            agent_cpp.insert(posDef + SEARCH_REACTIVE_H.length(), valuesToInsert);
            // Find registration position in the source file
            posReg = agent_cpp.find(SEARCH_FUNCT);
            // Generate values to insert for functSEARCH_Hion registration
            valuesToInsert = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_FUNCTION_REG], service[SERVICE], funct[NAME]);
            // Insert function registration into the source file
            agent_cpp.insert(posReg + SEARCH_FUNCT.length(), valuesToInsert);
        }
    }

    // Insert initial message definition if the agent ID is 1 (manager)
    if (agentId == MANAGER_ID) {
        initMessage(agent_h, agent_cpp, REACTIVE_REASONING);
    }

    // Save modified files
    std::string fileName = fmt::format(resources[REACTIVE][TEMPLATE][TEMP_REACTIVE_FILE_NAME], agentId);
    fileManager->saveFile(path, fileName + ".h", agent_h);
    fileManager->saveFile(path, fileName + ".cpp", agent_cpp);
}


void AgentGenerator::processPetriNet(json data, std::string path, int agentId) {
    // Deep copy the template files
    std::string agent_h = fmt::format(resources[PETRI_NET][FILE_H], agentId);
    std::string agent_cpp = fmt::format(resources[PETRI_NET][FILE_CPP], agentId, agentId, agentId);

    // Initialize positions for insertion points
    size_t posH, posDef, serReg, posReg;
    std::string valuesToInsert, name;

    // Loop over attributes
    posH = agent_h.find(SEARCH_ATR);
    for (std::string atrId : data[ATTRIBUTES]) {
        // Retrieve attribute data
        json atr = data[atrId];
        // Generate values to insert for attributes
        valuesToInsert = fmt::format(resources[MAIN][TEMPLATE][TEMP_ATTRIBUTE], atr[TYPE_ATR], atr[NAME], atr[INIT_VALUE]);
        // Insert values into the header file
        agent_h.insert(posH + SEARCH_ATR.length(), valuesToInsert);
    }

    // position in generated files
    posH = agent_h.find(SEARCH_NODES);
    posDef = agent_cpp.find(SEARCH_PETRI_NET_H);
    serReg = agent_cpp.find(SEARCH_SERVICE);
    posReg = agent_cpp.find(SEARCH_REGIST);

    // Set to store unique IDs of created nodes
    std::unique_ptr<std::unordered_set<std::string>> createdIds = std::make_unique<std::unordered_set<std::string>>();
    // Current IDs that have to be created
    // It is queue because of the else condition (more than one linked node)
    std::unique_ptr<UniqueDeque> currentIds = std::make_unique<UniqueDeque>();

    // Loop over all nodes
    for (std::string serviceId : data[SERVICES]) {
        // Retrieve service data
        json service = data[serviceId];
        std::string linkedId = std::string(service[LINKED]);
        // Skip empty linked nodes
        if (linkedId.empty())
            continue;
        // Save linked
        currentIds->push_back(linkedId);
        // Generate values to insert for service registration
        valuesToInsert = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_SERVICE_REG], serviceId, linkedId);
        // Insert function registration into the source file
        agent_cpp.insert(serReg + SEARCH_SERVICE.length(), valuesToInsert);

        // Iterate through all nodes of service Petri net
        while (!currentIds->empty()) {
            // Get id data
            std::string currId = currentIds->pop_front();
            // Check if node already exists
            if (createdIds->find(currId) != createdIds->end()) {
                // node exists
                continue;
            }
            // Save id
            createdIds->insert(currId);
            // Get data
            json node = data[currId];
            // Create based on node type
            // Name = type + nodeID
            switch (static_cast<int>(node[TYPE])) {
                case CONDITION_ID:
                    name = CONDITION + currId;
                    valuesToInsert = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_IF_ELSE_NODE_IMPL], agentId, name, node[IF], node[ELSE]);
                    currentIds->push_back(std::string(node[IF]));
                    currentIds->push_back(std::string(node[ELSE]));
                    break;
                case CODE_ID:
                    name = CODE + currId;
                    valuesToInsert = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_NODE_IMPL], agentId, name, node[LINKED]);
                    currentIds->push_back(std::string(node[LINKED]));
                    break;
                case FUNCTION_ID:
                    name = FUNCTION + currId;
                    valuesToInsert = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_NODE_IMPL], agentId, name, '{}');
                    break;
            }
            // Insert node implementation into the implementation
            agent_cpp.insert(posDef + SEARCH_PETRI_NET_H.length(), valuesToInsert);

            // Generate values to insert for node definition
            valuesToInsert = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_NODE_DEF], name);
            // Insert node definition into the header file
            agent_h.insert(posH + SEARCH_NODES.length(), valuesToInsert);
            // Generate values to insert for node registration
            valuesToInsert = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_NODE_REG], currId, name);
            // Insert node registration into the source file
            agent_cpp.insert(posReg + SEARCH_REGIST.length(), valuesToInsert);
        }
    }

    // Insert initial message definition if the agent ID is 1 (manager)
    if (agentId == MANAGER_ID) {
        initMessage(agent_h, agent_cpp, PETRI_NET_REASONING);
    }

    // Save modified files
    std::string fileName = fmt::format(resources[PETRI_NET][TEMPLATE][TEMP_PETRI_NET_FILE_NAME], agentId);
    fileManager->saveFile(path, fileName + ".h", agent_h);
    fileManager->saveFile(path, fileName + ".cpp", agent_cpp);
}

void AgentGenerator::initMessage(std::string& agent_h, std::string& agent_cpp, std::string type) {
    size_t pos = agent_h.find(SEARCH_OVERRIDE);
    // Insert template definition at position after SEARCH_OVERRIDE
    agent_h.insert(pos + SEARCH_OVERRIDE.length(), resources[MAIN][TEMPLATE][TEMP_MAIN_INITMSG_DEF]);
    // Format values for function registration and insert into agent_cpp
    std::string valuesToInsert = fmt::format(resources[MAIN][TEMPLATE][TEMP_MAIN_INITMSG_IMPL], MANAGER_ID, type);
    agent_cpp.insert(pos + SEARCH_REACTIVE_H.length(), valuesToInsert);
}

void AgentGenerator::processMain(json data) {

}
