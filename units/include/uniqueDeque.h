#pragma once
#include <deque>
#include <unordered_set>
#include <stdexcept>

/**
 * @class UniqueDeque
 * @brief A deque implementation that ensures uniqueness of its elements.
 * @tparam T The type of elements stored in the deque.
 */
template <typename T>
class UniqueDeque {
private:
    std::deque<T> deque;                // The deque to store elements
    std::unordered_set<T> set;          // The set to ensure uniqueness

    /**
     * @brief Private helper function to check if a value is unique.
     *
     * @param value The value to check for uniqueness.
     * @return `true` if the value is not already in the set, `false` otherwise.
     */
    bool uniqueValue(const T& value);

public:
    /**
     * @brief Default constructor for the UniqueDeque class.
     */
    UniqueDeque() = default;

    /**
     * @brief Adds a single element to the back of the deque.
     *
     * @param value The value to be added to the deque.
     * @return `true` if the element was added successfully, `false` if the element was a duplicate.
     */
    bool push_back(const T& value);

    /**
     * @brief Adds multiple elements from another deque.
     *
     * @param values The deque of values to be added to the current deque.
     * @return `true` if any element was added successfully, `false` otherwise.
     */
    bool push_back(const std::deque<T>& values);

    /**
     * @brief Removes and returns the element from the front of the deque.
     *
     * @return The value removed from the front of the deque.
     * @throws std::runtime_error If the deque is empty.
     */
    T pop_front();

    /**
     * @brief Checks if the deque is empty.
     *
     * @return `true` if the deque is empty, `false` otherwise.
     */
    bool empty() const;
};

template <typename T>
bool UniqueDeque<T>::uniqueValue(const T& value) {
    return set.find(value) == set.end();
}

template <typename T>
bool UniqueDeque<T>::push_back(const T& value) {
    if (uniqueValue(value)) {
        deque.push_back(value);
        set.insert(value);
        return true;
    }
    return false;
}

template <typename T>
bool UniqueDeque<T>::push_back(const std::deque<T>& values) {
    // Push only unique values
    bool addedAny = false;
    for (const auto& value : values) {
        if (uniqueValue(value)) {
            addedAny |= push_back(value);
        }
    }
    return addedAny;
}

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

template <typename T>
bool UniqueDeque<T>::empty() const {
    return deque.empty();
}