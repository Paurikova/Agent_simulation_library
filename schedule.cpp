#include "schedule.h"

void Schedule::pushMessage(Message message) {
    priorityQueue.push(message);
}

Message* Schedule::popMessage(int currTime) {
    if (priorityQueue.empty()) {
        return nullptr;
    }
    Message topMessage = priorityQueue.top();
    if (topMessage.time <= currTime) {
        //make copy
        Message* message = new Message(topMessage);
        priorityQueue.pop();
        return message;
    }
    return nullptr;
}
