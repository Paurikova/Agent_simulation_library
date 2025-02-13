#include "../include/configReader.h"

ConfigReader::ConfigReader(const std::string& filename) {
    loadConfig(filename);
}

std::string ConfigReader::get(const std::string& key) {
    if (config.find(key) != config.end()) {
        return config[key];
    } else {
        throw std::runtime_error(fmt::format("Key {} not found in config", key));
    }
}

void ConfigReader::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        throw std::runtime_error(fmt::format("Could not open config file: {}", filename));
    }

    while (std::getline(file, line)) {
        // Ignore empty lines and comments
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string key, value;

        // Split line into key and value (separated by '=')
        if (std::getline(ss, key, '=') && std::getline(ss, value)) {
            config[key] = value;
        }
    }
    file.close();
}