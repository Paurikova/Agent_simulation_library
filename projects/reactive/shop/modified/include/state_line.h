#pragma once
#include "../../../../../library/include/types_library.h"
#include "../../../../../library/include/state.h"

#include <queue>

struct StateLine : public State {
    int line = 0;

    StateLine(int pLine) : line (pLine) {};
};
