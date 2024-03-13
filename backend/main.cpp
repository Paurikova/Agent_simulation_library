#pragma once
#include "managerAgent.h"
#include "agents/agent1.h"
#include "agents/agent2.h"


int main() {
    ManagerAgent manager(0,10);
    //ID 2
    Agent1 agent1(2);
    //register agent
    manager.registerAgent(&agent1);
    Agent2 agent2(3);
    manager.registerAgent(&agent2);
    //add Message to agent1 schedule
    Message m1 = {1,1,1,-1,2};
    Message m2 = {1,3,1,-1,2};
    Message m3 = {1,4,1,-1,2};
    Message m4 = {1,5,1,-1,2};
    Message m5 = {1,6,1,-1,2};
    Message m6 = {1,7,1,-1,2};
    agent1.receiveMessage(m1);
    agent1.receiveMessage(m2);
    agent1.receiveMessage(m3);
    agent1.receiveMessage(m4);
    agent1.receiveMessage(m5);
    agent1.receiveMessage(m6);
    //run sim
    manager.runSimulation();
}
