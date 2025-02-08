#pragma once
#include "../library/include/state.h"

struct StateShop : public State {
    int customers = 0;
    int custInShop = 0;
    int custInLine[2] = {0, 0};
    int totalCustInLine[2] = {0, 0};
    int shoppingTime = 0;
    int waitingTime[2] = {0, 0};
    int payedTime[2] = {0, 0};
    StateShop() : State() {};
};
