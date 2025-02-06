#pragma once
#include <deque>
#include <unordered_set>
#include <stdexcept>

template <typename T>
class UniqueDeque {
private:
    std::deque<T> deque;                // The deque to store elements
    std::unordered_set<T> set;          // The set to ensure uniqueness

    // Private helper to check if a value is unique
    bool uniqueValue(const T& value);

public:
    UniqueDeque() = default;

    // Add a single element to the back of the deque
    bool push_back(const T& value);

    // Add multiple elements from another deque
    bool push_back(const std::deque<T>& values);

    // Remove and return the element from the front of the deque
    T pop_front();

    // Check if the deque is empty
    bool empty() const;
};
