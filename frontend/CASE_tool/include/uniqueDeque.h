#pragma once
#include <deque>
#include <unordered_set>
#include <stdexcept>

class UniqueDeque {
private:
    std::deque<std::string> deque;
    std::unordered_set<std::string> set;
private:
    bool uniqueValue(std::string pData);
public:
    UniqueDeque() = default;
    bool push_back(std::string pData);
    bool push_back(std::deque<std::string> pData);
    std::string pop_front();
    bool empty() const;
};