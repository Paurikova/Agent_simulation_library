#pragma once
#include <fmt/format.h>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

#include "fileManager.h"

/**
 * @class Logger
 * @brief A class to handle logging messages either to the console or a log file.
 */
class Logger {
private:
    FileManager* fileManager = new FileManager();
    bool console;
    std::string data;
    std::string path = "/home/miska/CLionProjects/Agent_simulation_library/logs";

    /**
     * @brief Private helper function to add log data to the file.
     */
    void addToFile();
public:
    /**
     * @brief Public method to log a message.
     *
     * @param msg The message to be logged.
     */
    void log(std::string msg);

    /**
     * @brief Constructor that initializes the `Logger` instance.
     *
     * @param pConsole A boolean flag to determine where to log the messages (default is `true`).
     */
    Logger(bool pConsole = true) : console(pConsole) {};


    /**
     * @brief Destructor that cleans up resources used by the `Logger` instance.
     */
    ~Logger();
};