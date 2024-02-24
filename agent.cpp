#include "agent.h"

// Adds a goal to the agent's list of goals.
void Agent::addGoal(Goal* goalPtr_) {
    goals.push(goalPtr_);
}

// Processes the next goal in the agent's queue.
void Agent::processGoal() {
    while (!goals.empty()) {
        // Process the front goal
        Goal* currentGoalPtr = goals.front();
        currentGoalPtr->process();
        goals.pop();
    }
}

