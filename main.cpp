#include "library/include/simulationCore.h"
#include "backend/agents/agent1.h"
#include "backend/agents/agent2.h"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <fstream>

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

using namespace nlohmann;

int main(int argc, char** argv) {
    SimulationCore* manager = new SimulationCore(0,10);
    //ID 2
    Agent1* agent1 = new Agent1(2, manager);
    //register agent
    manager->registerAgent(agent1);
    Agent2* agent2 = new Agent2(3, manager);
    manager->registerAgent(agent2);

    //add Message to agent1 schedule
    Message m1 = {1,1,1,1,-1};
    manager->pushToMainSchedule(&m1);
    Message m2 = {2,1,2,1,-1};
    manager->pushToMainSchedule(&m2);
    Message m3 = {4,2,1,-1,2};
    manager->pushToMainSchedule(&m3);
    Message m4 = {5,1,1,-1,2};
    manager->pushToMainSchedule(&m4);
    Message m5 = {7,1,1,-1,2};
    manager->pushToMainSchedule(&m5);
    Message m6 = {8,1,1,-1,2};
    manager->pushToMainSchedule(&m6);
    //run sim
    manager->runSimulation();
    return 0;
}