#include "../library/include/state.h"

struct StateNeighbor : public State {
    int neighbor;
    StateNeighbor(int neighbor) : neighbor(neighbor) {};
};