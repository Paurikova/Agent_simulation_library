#pragma once
#include <queue>
#include "goal.h"

/**
 * @brief Represents an agent capable of processing goals.
 *
 * Created by Paurikova on 24.2.2024.
 *
 * The Agent class models an entity capable of receiving, storing, and processing
 * goals to accomplish specific tasks or objectives. Each agent has a unique identifier
 * and maintains a queue of goals to be processed sequentially.
 */
class Agent {
private:
    int id;
    std::queue<Goal*> goals;
public:
    /**
     * @brief Constructs a new Agent object with the specified identifier.
     *
     * The constructor initializes a new Agent object with the unique identifier
     * provided as a parameter, which uniquely identifies it within the system.
     *
     * @param id_ The unique identifier of the agent.
     */
    Agent(int id_): id(id_) {};

    /**
     * @brief Adds a goal to the agent's list of goals.
     *
     * This method adds a new goal to the agent's list of goals.
     *
     * @param goal_ The pointer to goal to be added.
     */
    void addGoal(Goal* goalPtr_);

    /**
     * @brief Processes the next goal in the agent's queue.
     *
     * This method dequeues the next goal from the agent's queue of goals
     * and processes it. Processing involves determining the necessary actions
     * to achieve the goal and executing those actions accordingly.
     *
     * If the agent's queue is empty, the method does nothing.
     *
     * @post If a goal is successfully processed, it is removed from the queue.
     */
    void processGoal();
};
