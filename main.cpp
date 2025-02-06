#include "library/include/simulationCore.h"

#include "Obchod_better/manager.h"
#include "Obchod_better/customer.h"
#include "Obchod_better/shop.h"
#include "Obchod_better/line.h"
#include "Obchod_better/cash.h"
#include "Obchod_better/state.h"
//#include "flocking_model/manager.h"
//#include "flocking_model/bird.h"
//#include "flocking_model/bird.h"


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

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

//
//int main() {
//    srand(time(0)); // Initialize random number generator
//
//    // Create a flock of birds
//    int n_birds = 300;
//    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
//    Manager* manager = new Manager(1.5, 0.1, 2.0, 0.25, 0.04, 50.0, n_birds, window);
//    SimulationCore* simCore = new SimulationCore(manager);
//    for (int i = 0; i < n_birds; i++) {
//        simCore->registerAgent(new Agent(i + 2, simCore, new Bird(window)));
//    }
//
//    // Run the simulation
//    simCore->runSimulation();
//    return 0;
//}

int main(int argc, char** argv) {
    Logger* logger = new Logger();
    Manager* manager = new Manager(10, 1, logger);
    SimulationCore* simCore = new SimulationCore(manager, logger);
    Customer* cust = new Customer(logger);
    Agent* aCustomer = new Agent(2, simCore, cust);
    simCore->registerAgent(aCustomer);
    State* state1 = new State();
    State* state2 = new State();
    Shop* rShop = new Shop(1, state1, state2, logger);
    Agent* aShop = new Agent(3, simCore, rShop);
    simCore->registerAgent(aShop);
    Line* rLineManager1 = new Line(state1, logger);
    Line* rLineManager2 = new Line(state2, logger);
    Agent* line1 = new Agent(4, simCore, rLineManager1);
    Agent* line2 = new Agent(5, simCore, rLineManager2);
    simCore->registerAgent(line1);
    simCore->registerAgent(line2);
    Cash* rCash1 = new Cash({2}, 3, 11, logger);
    Cash* rCash2 = new Cash({6}, 3, 11, logger);
    Agent* aCash1 = new Agent(6, simCore, rCash1);
    Agent* aCash2 = new Agent(7, simCore, rCash2);
    simCore->registerAgent(aCash1);
    simCore->registerAgent(aCash2);
    simCore->runSimulation();
    delete logger;
//
////    SimCoreReactiveReasoning* simCoreReasoning = new SimCoreReactiveReasoning();
////    SimulationCore* manager = new SimulationCore(simCoreReasoning);
////    Agent1PetriNetReasoning* agent1Reasoning = new Agent1PetriNetReasoning();
////    Agent* agent1 = new Agent(2, manager, agent1Reasoning);
////    manager->registerAgent(agent1);
////    Agent3ReactiveReasoning* agent3Reasoning = new Agent3ReactiveReasoning();
////    Agent* agent3 = new Agent(4, manager, agent3Reasoning);
////    manager->registerAgent(agent3);
////    //ID 2
////    Agent1ReactiveReasoning* agent1Reasoning = new Agent1ReactiveReasoning();
////    Agent* agent1 = new Agent(2, manager, agent1Reasoning);
////    //register agent
////    manager->registerAgent(agent1);
////    Agent2ReactiveReasoning* agent2Reasoning = new Agent2ReactiveReasoning();
////    Agent* agent2 = new Agent(3, agent1, agent2Reasoning);
////    manager->registerAgent(agent2);
//
//
//    //add Message to agent1 schedule
////    Message m1 = {5.,1,1,1,2};
////    manager->pushToMainSchedule(&m1);
////    Message m2 = {2.,1,2,1,-1};
////    manager->pushToMainSchedule(&m2);
////    Message m3 = {4.,2,1,-1,3};
////    manager->pushToMainSchedule(&m3);
//    //run sim
//   // manager->runSimulation();
//
//
    return 0;
}