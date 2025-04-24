#pragma once

#include <vector>
#include <utility>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <unordered_set>

#include "types_frontend.h"
#include "fileManager.h"
#include "uniqueDeque.h"

using json = nlohmann::json;

/**
 * @brief The AgentGenerator class provides functionality to generate agent files based on JSON data.
 */
class AgentGenerator {
private:
    const std::string RESOURCE_PATH = "[path to library]/frontend/CASE_tool";
    // reactive templates
    const std::string TEMPLATE_REACTIVE_JSON = "templatesReactive.json"; /**< Default template JSON file name. */
    const std::string CLASS_REACTIVE_H = "templateReactive_h.txt"; /**< Default template header file name. */
    const std::string CLASS_REACTIVE_CPP = "templateReactive_cpp.txt"; /**< Default template source file name. */
    const std::string OUTPUT_REACTIVE_FILE = "outputReactive.json"; /**< Default output JSON file name. */
    const std::string RESOURCE_REACTIVE_PATH = RESOURCE_PATH + "/resources/reactive"; /**< Default path to resources. */

    // petri nete templates
    const std::string TEMPLATE_PETRINET_JSON = "templatesPetriNet.json"; /**< Default template JSON file name. */
    const std::string CLASS_PETRINET_H = "templatePetriNet_h.txt"; /**< Default template header file name. */
    const std::string CLASS_PETRINET_CPP = "templatePetriNet_cpp.txt"; /**< Default template source file name. */
    const std::string OUTPUT_PETRINET_FILE = "outputPetriNet.json"; /**< Default output JSON file name. */
    const std::string RESOURCE_PETRINET_PATH = RESOURCE_PATH + "/resources/petriNet"; /**< Default path to resources. */

    // main templates
    const std::string TEMPLATE_MAIN_JSON = "templateMain.json"; /**< Default template JSON file name. */
    const std::string CLASS_MAIN_CPP = "templateMain_cpp.txt"; /**< Default output main JSON file name. */
    const std::string RESOURCE_MAIN_PATH = RESOURCE_PATH + "/resources"; /**< Default path to resources. */

    std::unique_ptr<FileManager> fileManager;
    nlohmann::json outputJson; /**< JSON object to store output data. */
    nlohmann::json resources; /**< JSON object to store resource data. */
    std::map<int, int> node2Agent; /**< Map to store node-to-agent mappings. */
public:
    /**
     * @brief Constructs an AgentGenerator object.
     *
     * @param pPath path to working dir
     */
    AgentGenerator();

    /**
     * @brief Processes the input JSON data to generate agent files.
     * @param data The input JSON data.
     */
    void processJson(json data, std::string path);

private:
    /**
     * @brief Processes the creation of a reactive agent by generating its header and source files.
     *
     * @param data A JSON object containing the agent configuration (attributes, services, etc.).
     * @param path The path where the generated files will be saved.
     * @param agentId The ID of the agent.
     * @param agentName The name of the agent.
     */
    void processReactive(json data, std::string path, int agentId, std::string agentName);

    /**
     * @brief Processes the creation of a Petri Net-based agent by generating its header and source files.
     *
     * @param data A JSON object containing the agent configuration (attributes, services, etc.).
     * @param path The path where the generated files will be saved.
     * @param agentId The ID of the agent.
     * @param agentName The name of the agent.
     */
    void processPetriNet(json data, std::string path, int agentId, std::string agentName);

    /**
    * @brief Inserts an initial message definition for the main agent initialization.
    *
    * @param agent_h A reference to the header file content.
    * @param agent_cpp A reference to the source file content.
    * @param type The type of reasoning (e.g., reactive or Petri net).
    * @param searchType Searching type.
     * @param agentName The name of the agent.
     *
     */
    void initMessage(std::string& agent_h, std::string& agent_cpp, std::string type, std::string searchType, std::string agentName);
};