#pragma once
#include <iostream>
#include <vector>
#include <queue>

#include "message.h"

class Schedule {
private:
    std::priority_queue<Message, std::vector<Message>, MessageComparator> priorityQueue;
public:
    void pushMessage(Message message);
    Message* popMessage(int time);
};
