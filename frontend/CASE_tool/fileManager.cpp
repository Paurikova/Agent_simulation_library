#include "fileManager.h"

std::string FileManager::readFile(std::string path, std::string name) {
    // Concatenate the path and name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, name);

    // Open the file
    std::ifstream fileSource(fullName);

    // Check if the file is successfully opened
    if (!fileSource.is_open()) {
        throw std::runtime_error(fmt::format("Error: Unable to open file {}.", fullName));
    }

    // Read the content of the file into a string
    std::string file_str((std::istreambuf_iterator<char>(fileSource)), std::istreambuf_iterator<char>());

    // Close the file
    fileSource.close();

    // Return the file content as a string
    return file_str;
}

json FileManager::readJson(std::string path, std::string name) {
    // Concatenate the path and name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, name);

    // Open the JSON file
    std::ifstream fileSource(fullName);

    // Check if the file is successfully opened
    if (!fileSource.is_open()) {
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

void FileManager::saveFile(std::string path, std::string fileName, std::string data) {
    // Concatenate the path and file name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, fileName);

    // Create an ofstream object
    std::ofstream outfile;

    // Open the file (this will create the file if it doesn't exist)
    outfile.open(fullName);

    // Check if the file is successfully opened
    if (!outfile.is_open()) {
        throw std::runtime_error(fmt::format("Error: Unable to save file {}.", fullName));
    }

    // Write data to the file
    outfile << data;

    // Close the file
    outfile.close();
}

void FileManager::saveJson(std::string path, std::string fileName, json data) {
    // Concatenate the path and file name to form the full file name
    std::string fullName = fmt::format("{}/{}", path, fileName);

    // Create an ofstream object
    std::ofstream outfile;

    // Open the file (this will create the file if it doesn't exist)
    outfile.open(fullName);

    // Check if the file is successfully opened
    if (!outfile.is_open()) {
        throw std::runtime_error(fmt::format("Error: Unable to save file {}.", fullName));
    }

    // Write JSON data to the file
    outfile << data.dump(4); // 4 is the indentation level for pretty printing

    // Close the file
    outfile.close();
}
