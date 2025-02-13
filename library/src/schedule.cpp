#include "../include/schedule.h"

const SimTime_t Schedule::SIMULATION_TIME_OFFSET = 0;

void Schedule::pushMessage(Message* message) {
    priorityQueue.push(message);
}

Message* Schedule::popMessage(SimTime_t currTime, SimTime_t offset) {
    if (priorityQueue.empty()) {
        return nullptr;
    }
    Message* topMessage = priorityQueue.top();
    if (topMessage->execTime <= currTime + offset) { // Check if the top message's time has elapsed
        priorityQueue.pop();
        return topMessage;
    }
    return nullptr;
}

Message* Schedule::popMessage() {
    if (priorityQueue.empty()) {
        return nullptr;
    }
    Message* topMessage = priorityQueue.top();
    priorityQueue.pop();
    return topMessage;
}