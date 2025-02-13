#pragma once
#include "../../../../library/include/state.h"

struct StateMove : public State {
    float cohereX = 0, cohereY = 0, separateX = 0, separateY = 0, matchX = 0, matchY = 0;
    StateMove() {};

};