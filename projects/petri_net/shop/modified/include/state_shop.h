#pragma once
#include "../../../../../library/include/types_library.h"
#include "../../../../../library/include/state.h"

#include <queue>

struct StateShop : public State {
    float customers = 0;
    float custInShop = 0;
    std::unordered_map<int,  std::queue<float>> custInLines;
    std::unordered_map<int, float> totalCustTimeInLine = {{4, 0}, {5, 0}};
    std::unordered_map<int, int> totalCustInLine = {{4, 0}, {5, 0}};
    float shoppingTime = 0;
    StateShop() : State() {
        // Add empty queues to the map
        custInLines[4] = std::queue<float>();
        custInLines[5] = std::queue<float>();
    };
};
