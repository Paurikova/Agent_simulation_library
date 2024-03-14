#pragma once

#include <iostream>
#include <vector>
#include <queue>

#include "message.h"

/**
 * @brief The Schedule class represents a schedule for storing and managing scheduled messages.
 */
class Schedule {
private:
    static const SimTime_t SIMULATION_TIME_OFFSET;
    /**
     * @brief priorityQueue is a priority queue to store pointers to Message objects.
     * The messages are ordered based on their scheduled execution time and priority.
     */
    std::priority_queue<Message*, std::vector<Message*>, MessagePtrComparator> priorityQueue;

public:
    /**
     * @brief Pushes a message pointer into the schedule.
     *
     * @param pMsg Pointer to the Message object to be pushed.
     */
    void pushMessage(Message* pMsg);

    /**
     * @brief Pops the top message pointer from the schedule.
     *
     * @param pTime Simulation time to check for scheduled messages.
     * @param pOffset Offet for simulation time until we can performed all messages (optional, default is const)
     * @return Pointer to the top Message object, or nullptr if no message is scheduled at pTime.
     */
    Message* popMessage(SimTime_t currTime, SimTime_t pOffset = SIMULATION_TIME_OFFSET);

    /**
     * @brief Pops the top message pointer from the schedule.
     *
     * @return Pointer to the top Message object, or nullptr if no message is scheduled at pTime.
     */
    Message* popMessage();
};
