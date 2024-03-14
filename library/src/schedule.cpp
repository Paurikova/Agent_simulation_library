#include "../include/schedule.h"

const SimTime_t Schedule::SIMULATION_TIME_OFFSET = 0;

void Schedule::pushMessage(Message* message) {
    // Pushes a message into the schedule.
    priorityQueue.push(message);
}

Message* Schedule::popMessage(SimTime_t currTime, SimTime_t offset) {
    if (priorityQueue.empty()) {
        return nullptr; // Return nullptr if the priority queue is empty
    }
    Message* topMessage = priorityQueue.top();
    if (topMessage->execTime <= currTime + offset) { // Check if the top message's time has elapsed
        priorityQueue.pop(); // Remove the top message from the priority queue
        return topMessage;
    }
    return nullptr; // Return nullptr if the top message's time hasn't elapsed
}

Message* Schedule::popMessage() {
    if (priorityQueue.empty()) {
        return nullptr; // Return nullptr if the priority queue is empty
    }
    Message* topMessage = priorityQueue.top();
    priorityQueue.pop(); // Remove the top message from the priority queue
    return topMessage;
}