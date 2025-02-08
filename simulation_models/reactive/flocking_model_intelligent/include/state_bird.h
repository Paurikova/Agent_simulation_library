#pragma once
#include "include/state.h"

struct StateBird : public State {
    float x, y; //position
    float velX, velY; //velocity
    StateBird(float x, float y, float velX, float velY) : x(x), y(y), velX(velX), velY(velY) {};
};