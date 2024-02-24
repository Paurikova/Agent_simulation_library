#include <iostream>
#include "agent.h"
#include "goal.h"
#include "action.h"
#include "helloAction.h"

int main() {
    HelloAction action("hello");
    Goal goal(&action);
    Agent agent(0);
    agent.addGoal(&goal);
    agent.processGoal();
    return 0;
}
