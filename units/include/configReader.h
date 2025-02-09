#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <fmt/core.h>
#include <stdexcept>

class ConfigReader {
private:
    std::unordered_map<std::string, std::string> config;
    void loadConfig(const std::string& filename);

public:
    std::string get(const std::string& key);
    ConfigReader(const std::string& filename);
};