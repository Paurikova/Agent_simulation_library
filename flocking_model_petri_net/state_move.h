#pragma once
#include "../library/include/state.h"

struct StateMove : public State {
    float matchX = 0, matchY= 0, separateX = 0, separateY =0, cohereX = 0, cohereY = 0;
    int i = 1, N = 0;
};