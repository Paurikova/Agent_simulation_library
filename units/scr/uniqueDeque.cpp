#include "../include/uniqueDeque.h"

// Template specialization for NodeId_t or any type T
template <typename T>
bool UniqueDeque<T>::uniqueValue(const T& value) {
    return set.find(value) == set.end();
}

// Template specialization for NodeId_t or any type T
template <typename T>
bool UniqueDeque<T>::push_back(const T& value) {
    if (uniqueValue(value)) {
        // If not found, insert into both deque and set
        deque.push_back(value);
        set.insert(value);
        return true;
    }
    return false;
}

// Template specialization for NodeId_t or any type T
template <typename T>
bool UniqueDeque<T>::push_back(const std::deque<T>& values) {
    // Push only unique values
    bool addedAny = false;
    for (const auto& value : values) {
        // Check if the value is already in the set
        if (uniqueValue(value)) {
            addedAny |= push_back(value);
        }
    }
    return addedAny; // Return true if any element was added
}

// Template specialization for NodeId_t or any type T
template <typename T>
T UniqueDeque<T>::pop_front() {
    if (deque.empty()) {
        throw std::runtime_error("Deque is empty. Cannot pop value.");
    }
    T output = deque.front();
    deque.pop_front();
    auto it = set.find(output);
    if (it != set.end()) {
        set.erase(it); // Erase the element from the set
    } else {
        throw std::runtime_error("Erased value does not exist in set.");
    }
    return output;
}

// Template specialization for NodeId_t or any type T
template <typename T>
bool UniqueDeque<T>::empty() const {
    return deque.empty();
}