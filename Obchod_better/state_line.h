#pragma once
#include "../library/include/state.h"

struct StateLine : public State {
    int custInLine;
    StateLine() : State(), custInLine(0) {};
};
