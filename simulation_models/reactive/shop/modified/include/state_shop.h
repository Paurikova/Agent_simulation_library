#pragma once
#include "../../../../../library/include/types_library.h"
#include "../../../../../library/include/state.h"

#include <queue>

struct StateShop : public State {
    float customers = 0;
    float custInShop = 0;
    std::queue<float> custInLine0;
    std::queue<float> custInLine1;
    float totalCustTimeInLine0 = 0;
    float totalCustTimeInLine1 = 0;
    int totalCustInLine0 = 0;
    int totalCustInLine1 = 0;
    float shoppingTime = 0;

    StateShop() : State() {
    };
};
