#include "library/include/simulationCore.h"
#include "backend/include//simCoreReactiveReasoning.h"
#include "backend/include/agent1ReactiveReasoning.h"
#include "backend/include/agent2ReactiveReasoning.h"
#include "backend/include/agent3ReactiveReasoning.h"
#include "backend/include/agent1PetriNetReasoning.h"
#include "Obchod/manager.h"
#include "Obchod/customer.h"
#include "Obchod/line_manager.h"
#include "Obchod/cash_register.h"
#include "Obchod/shop.h"

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
    Manager* manager = new Manager();
    SimulationCore* simCore = new SimulationCore(manager);
    customer* cust = new customer();
    Agent* aCustomer = new Agent(2, simCore, cust);
    simCore->registerAgent(aCustomer);
    shop* rShop = new shop();
    Agent* aShop = new Agent(3, simCore, rShop);
    simCore->registerAgent(aShop);
    line_manager* rLineManager = new line_manager();
    Agent* aLineManager = new Agent(4, simCore, rLineManager);
    simCore->registerAgent(aLineManager);
    cash_register* rCash = new cash_register();
    Agent* aCash = new Agent(5, simCore, rCash);
    simCore->registerAgent(aCash);
    simCore->runSimulation();


//    SimCoreReactiveReasoning* simCoreReasoning = new SimCoreReactiveReasoning();
//    SimulationCore* manager = new SimulationCore(simCoreReasoning);
//    Agent1PetriNetReasoning* agent1Reasoning = new Agent1PetriNetReasoning();
//    Agent* agent1 = new Agent(2, manager, agent1Reasoning);
//    manager->registerAgent(agent1);
//    Agent3ReactiveReasoning* agent3Reasoning = new Agent3ReactiveReasoning();
//    Agent* agent3 = new Agent(4, manager, agent3Reasoning);
//    manager->registerAgent(agent3);
//    //ID 2
//    Agent1ReactiveReasoning* agent1Reasoning = new Agent1ReactiveReasoning();
//    Agent* agent1 = new Agent(2, manager, agent1Reasoning);
//    //register agent
//    manager->registerAgent(agent1);
//    Agent2ReactiveReasoning* agent2Reasoning = new Agent2ReactiveReasoning();
//    Agent* agent2 = new Agent(3, agent1, agent2Reasoning);
//    manager->registerAgent(agent2);


    //add Message to agent1 schedule
//    Message m1 = {5.,1,1,1,2};
//    manager->pushToMainSchedule(&m1);
//    Message m2 = {2.,1,2,1,-1};
//    manager->pushToMainSchedule(&m2);
//    Message m3 = {4.,2,1,-1,3};
//    manager->pushToMainSchedule(&m3);
    //run sim
   // manager->runSimulation();
    return 0;
}