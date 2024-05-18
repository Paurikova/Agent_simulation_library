#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fmt/format.h>
#include <iostream>
#include <string>

#include "types.h"

using json = nlohmann::json;

/**
 * @brief The AgentGenerator class provides functionality to generate agent files based on JSON data.
 */
class AgentGenerator {
private:
    const std::string TEMPLATE_JSON = "templates.json"; /**< Default template JSON file name. */
    const std::string CLASS_H = "templateClass_h.txt"; /**< Default template header file name. */
    const std::string CLASS_CPP = "templateClass_cpp.txt"; /**< Default template source file name. */
    const std::string OUTPUT_FILE = "output.json"; /**< Default output JSON file name. */
    //TODO absolute path
    const std::string RESOURCE_PATH = "/home/miska/CLionProjects/Agent_simulation_library/frontend/CASE_tool/resources"; /**< Default path to resources. */
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
    void processJson(json data);

private:
    /**
     * @brief Processes reactive agent data to generate header and source files.
     * @param data The reactive agent JSON data.
     * @param agentId The ID of the agent being processed.
     */
    void processReactive(json data, int agentId);

    /**
     * @brief Reads the content of a file and returns it as a string.
     * @param path The path to the file.
     * @param name The name of the file.
     * @return The content of the file as a string.
     */
    std::string readFile(std::string path, std::string name);

    /**
     * @brief Reads and parses a JSON file.
     * @param path The path to the JSON file.
     * @param name The name of the JSON file.
     * @return The parsed JSON data.
     */
    json readJson(std::string path, std::string name);

    /**
     * @brief Saves data to a file.
     * @param path The path to the directory where the file will be saved.
     * @param fileName The name of the file.
     * @param data The data to be written to the file.
     */
    void saveFile(std::string path, std::string fileName, std::string data);
};