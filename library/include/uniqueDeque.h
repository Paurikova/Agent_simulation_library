#pragma once
#include <deque>
#include <unordered_set>
#include <stdexcept>

#include "types.h"

class UniqueDeque {
private:
    std::deque<NodeId_t> deque;
    std::unordered_set<NodeId_t> set;
private:
    bool uniqueValue(NodeId_t pData);
public:
    UniqueDeque() = default;
    bool push_back(NodeId_t pData);
    bool push_back(std::deque<NodeId_t> pData);
    NodeId_t pop_front();
    bool empty() const;
};