#pragma once
#include "../library/include/state.h"

struct StateMove : public State {
    float cohereX, cohereY, separateX, separateY, matchX, matchY;
    StateMove(float cohereX,float cohereY,float separateX, float separateY, float matchX, float matchY) : cohereX(cohereX),
    cohereY(cohereY), separateX(separateX), separateY(separateY), matchX(matchX), matchY(matchY) {};
};