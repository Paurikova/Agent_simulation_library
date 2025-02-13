#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fmt/core.h>
#include <stdexcept>

/**
 * @class ConfigReader
 * @brief A class that handles reading configuration data from a file and provides access to the values.
 */
class ConfigReader {
private:
    std::unordered_map<std::string, std::string> config;

    /**
    * @brief Private helper function to load the configuration data from a file.
    *
    * @param filename The path to the configuration file to be read.
    */
    void loadConfig(const std::string& filename);

public:
    /**
    * @brief Constructor that initializes the ConfigReader with a configuration file.
    *
    * @param filename The path to the configuration file to be loaded.
    */
    ConfigReader(const std::string& filename);

    /**
     * @brief Retrieves the value associated with a given key.
     *
     * @param key The key whose associated value is to be retrieved.
     * @return The value associated with the key as a string.
     */
    std::string get(const std::string& key);
};