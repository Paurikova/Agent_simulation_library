#pragma once

struct Message {
    int id = -1;
    int time = -1;
    int priority = -1;
    int sender = -1;
    int receiver = -1;
};

// Comparator for priority queue to order events by time and priority
struct MessageComparator {
    bool operator()(const Message e1, const Message e2) const {
        if (e1.time == e2.time) {
            return e1.priority > e2.priority; // Higher priority first
        }
        return e1.time > e2.time; // Earlier time first
    }
};