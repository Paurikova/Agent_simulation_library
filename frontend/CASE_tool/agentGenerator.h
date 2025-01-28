#pragma once

#include <vector>
#include <utility>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <unordered_set>

#include "types.h"
#include "fileManager.h"
#include "../../structure/include/uniqueDeque.h"


using json = nlohmann::json;

/**
 * @brief The AgentGenerator class provides functionality to generate agent files based on JSON data.
 */
class AgentGenerator {
private:
    // reactive templates
    const std::string TEMPLATE_REACTIVE_JSON = "templatesReactive.json"; /**< Default template JSON file name. */
    const std::string CLASS_REACTIVE_H = "templateReactive_h.txt"; /**< Default template header file name. */
    const std::string CLASS_REACTIVE_CPP = "templateReactive_cpp.txt"; /**< Default template source file name. */
    const std::string OUTPUT_REACTIVE_FILE = "outputReactive.json"; /**< Default output JSON file name. */
    //TODO absolute path
    const std::string RESOURCE_REACTIVE_PATH = "/home/miska/CLionProjects/Agent_simulation_library/frontend/CASE_tool/resources/reactive"; /**< Default path to resources. */

    // petri nete templates
    const std::string TEMPLATE_PETRINET_JSON = "templatesPetriNet.json"; /**< Default template JSON file name. */
    const std::string CLASS_PETRINET_H = "templatePetriNet_h.txt"; /**< Default template header file name. */
    const std::string CLASS_PETRINET_CPP = "templatePetriNet_cpp.txt"; /**< Default template source file name. */
    const std::string OUTPUT_PETRINET_FILE = "outputPetriNet.json"; /**< Default output JSON file name. */
    //TODO absolute path
    const std::string RESOURCE_PETRINET_PATH = "/home/miska/CLionProjects/Agent_simulation_library/frontend/CASE_tool/resources/petriNet"; /**< Default path to resources. */

    // main templates
    const std::string TEMPLATE_MAIN_JSON = "templatesMain.json"; /**< Default template JSON file name. */
    //TODO absolute path
    const std::string RESOURCE_MAIN_PATH = "/home/miska/CLionProjects/Agent_simulation_library/frontend/CASE_tool/resources"; /**< Default path to resources. */

    std::unique_ptr<FileManager> fileManager;
    nlohmann::json outputJson; /**< JSON object to store output data. */
    nlohmann::json resources; /**< JSON object to store resource data. */
    std::map<int, int> node2Agent; /**< Map to store node-to-agent mappings. */
public:
    /**
     * @brief Constructs an AgentGenerator object.
     */
    AgentGenerator();

    /**
     * @brief Processes the input JSON data to generate agent files.
     * @param data The input JSON data.
     */
    void processJson(json data, std::string path);

private:
    /**
     * @brief Processes reactive agent data to generate header and source files.
     * @param data The reactive agent JSON data.
     * @param agentId The ID of the agent being processed.
     */
    void processReactive(json data, std::string path, int agentId);

    void processPetriNet(json data, std::string path, int agentId);

    void processMain(json data);
};