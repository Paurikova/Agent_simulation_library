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

class Logger {
private:
    FileManager* fileManager = new FileManager();
    bool console;
    std::string data;
    std::string path = "/home/miska/CLionProjects/Agent_simulation_library/logs";
    void addToFile();
public:
    void log(std::string msg);
    Logger(bool pConsole = true) : console(pConsole) {};
    ~Logger();
};