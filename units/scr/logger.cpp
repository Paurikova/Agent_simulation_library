#include "../include/logger.h"

void Logger::log(std::string msg) {
    // save data for log output
    data += msg;
    if (!console) return;
    // log to console
    std::cout << msg;
}

void Logger::addToFile() {
    // get current time for file name
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::localtime(&now_time_t);
    std::stringstream ss;
    ss << std::put_time(&tm, "%y%m%d_%H%M%S");  // Format as yyMMDDhhmmss
    fileManager->saveFile(path, fmt::format("{}.log", ss.str()), data);
}

Logger::~Logger() {
    addToFile();
}