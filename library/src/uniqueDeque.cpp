#include "../include/uniqueDeque.h"

bool UniqueDeque::uniqueValue(NodeId_t pData) {
    return set.find(pData) == set.end();
}

bool UniqueDeque::push_back(NodeId_t pData) {
    if (uniqueValue(pData)) {
        // If not found, insert into both deque and set
        deque.push_back(pData);
        set.insert(pData);
        return true;
    }
    return false;
}

bool UniqueDeque::push_back(std::deque<NodeId_t> pData) {
    // Push only unique values
    for (const auto& value : pData) {
        // Check if the nodeId is already in the set
        if (uniqueValue(value)) {
            push_back(value);
        }
    }
}

NodeId_t UniqueDeque::pop_front() {
    if (deque.empty()) {
        throw std::runtime_error("Deque is empty. Cannot pop value.");
    }
    NodeId_t output = deque.front();
    deque.pop_front();
    auto it = set.find(output);
    if (it != set.end()) {
        set.erase(it); // Erase the element pointed by the iterator
    } else {
        throw std::runtime_error("Erased value does not exist in set.");
    }
    return output;
}

bool UniqueDeque::empty() const {
    return deque.empty();
}