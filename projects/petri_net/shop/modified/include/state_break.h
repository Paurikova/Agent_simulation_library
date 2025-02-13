#pragma once
#include "../../../../../library/include/types_library.h"
#include "../../../../../library/include/state.h"

#include <queue>

struct StateBreak : public State {
    int cashBreak;
    StateBreak(int pBreak) : State(), cashBreak(pBreak){};
    StateBreak() {};
};
