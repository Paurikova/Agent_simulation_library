#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <unordered_map>

#include "schedule.h"
class Agent {
protected:
    using Funct = std::function<void(int)>;
private:
    int id;
    int currTime;
    //true if this is the first check in the given tick,
    // or if any message has been delivered in the given agent tick
    bool execute;
    std::vector<Message>* outBox = new std::vector<Message>();
    //map maps functions to message IDs
    std::unordered_map<int, Funct> functionMap;
    Schedule* schedule = new Schedule();
private:
    void process(int eventId, int sender);
protected:
    int getCurrTime();
    void sendMessage(int id, int receiver, int time, int priority = -1);
    void registerFunction(int eventId, Funct func);
    void unregisterFunction(int eventId);
public:
    Agent(int id_) : id(id_) {};
    int getId() {return id;}
    void setExecute(bool pExecute);
    bool getExecute();
    Message getTopMessage();
    Message receiveMessage(Message msg);
    void doTick(int time);
    virtual void registerFunctions() = 0;
};
