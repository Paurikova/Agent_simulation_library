#pragma once

#include <string>

using namespace std;

/**
 * @brief Represents an abstract action with customizable processing behavior.
 *
 * Created by Paurikova on 24.2.2024.
 *
 * The Action class defines an abstract representation of actions that can be performed
 * within a system. Each action is associated with a name and can perform custom processing
 * logic defined by derived classes.
 */
class Action {
private:
    string name; /** Unique name of the action. */

public:
    /**
     * @brief Constructs a new Action object with the specified name.
     *
     * Upon construction, the Action object is associated with the given name,
     * which identifies the type or purpose of the action.
     *
     * @param name_ The name associated with the action.
     */
    Action(string name_): name(name_) {};

    /**
     * @brief Virtual method to process the action.
     *
     * This method is virtual, it can be overridden by derived classes.
     * It processing behavior of the action.
     *
     * @see Derived classes for specific implementations of action processing.
     */
    virtual void process() = 0;
};
