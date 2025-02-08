#pragma once
#include "include/state.h"

struct StateShop : public State {
    float customers = 0;
    float custInShop = 0;
    float custInLine[2] = {0, 0};
    float totalCustInLine[2] = {0, 0};
    float shoppingTime = 0;
    float waitingTime[2] = {0, 0};
    float payedTime = 0;
    StateShop() : State() {};
};
