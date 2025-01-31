#include "../include/uniqueDeque.h"

bool UniqueDeque::uniqueValue(std::string pData) {
    return set.find(pData) == set.end();
}

// Template specialization for std::string or any type T
bool UniqueDeque::push_back(const std::string value) {
    if (uniqueValue(value)) {
        // If not found, insert into both deque and set
        deque.push_back(value);
        set.insert(value);
        return true;
    }
    return false;
}

bool UniqueDeque::push_back(std::deque<std::string> pData) {
    // Push only unique values
    bool addedAny = false;
    for (const auto& value : pData) {
        // Check if the value is already in the set
        if (uniqueValue(value)) {
            addedAny |= push_back(value);
        }
    }
    return addedAny; // Return true if any element was added
}

std::string UniqueDeque::pop_front() {
    if (deque.empty()) {
        throw std::runtime_error("Deque is empty. Cannot pop value.");
    }
    std::string output = deque.front();
    deque.pop_front();
    auto it = set.find(output);
    if (it != set.end()) {
        set.erase(it); // Erase the element from the set
    } else {
        throw std::runtime_error("Erased value does not exist in set.");
    }
    return output;
}

bool UniqueDeque::empty() const {
    return deque.empty();
}