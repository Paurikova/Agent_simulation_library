#pragma once
#include <nlohmann/json.hpp>
#include <fmt/format.h>
#include <iostream>
#include <fstream>

using json = nlohmann::json;

class FileManager {
private:
public:
    FileManager() {};
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

    /**
     * @brief Saves data to a json.
     * @param path The path to the directory where the file will be saved.
     * @param fileName The name of the file.
     * @param data The data to be written to the json.
     */
    void saveJson(std::string path, std::string fileName, json data);
};