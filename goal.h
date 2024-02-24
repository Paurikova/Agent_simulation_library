#pragma once

#include <string>
#include "action.h"

using namespace std;
/**
 * @brief Represents a goal to be achieved within a plan.
 *
 * Created by Paurikova on 24.2.2024.
 *
 * Each goal is associated with a plan that outlines the steps
 * or actions required to accomplish the goal.
 */
class Goal {
private:
    string name;
    Action* actionPrt; /**< The action associated with the goal. */
public:
    /**
     * @brief Constructs a new Goal object with the specified action.
     *
     * The constructor initializes a new Goal object with the provided action.
     * Upon construction, the Goal object is associated with the given action,
     * which outlines the steps or actions necessary to achieve the goal.
     *
     * @param actionPrt_ The pointer to action associated with the goal.
     */
    Goal(Action* actionPrt_): actionPrt(actionPrt_){}

    /**
     * @brief Processes the goal by executing the associated action.
     *
     * This method initiates the processing of the goal by executing the steps
     * defined in the associated action.
     */
    void process();
};
