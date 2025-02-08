#include "library/include/simulationCore.h"

#include "simulation_models/reactive/shop/include/manager.h"
#include "simulation_models/reactive/shop/include/customer.h"
#include "simulation_models/reactive/shop/include/shop.h"
#include "simulation_models/reactive/shop/include/line.h"
#include "simulation_models/reactive/shop/include/cash.h"
#include "simulation_models/reactive/shop/include/state_shop.h"
#include "simulation_models/reactive/shop/include/graph.h"

int main(int argc, char** argv) {
    StateShop* stateShop = new StateShop();
    Logger* logger = new Logger();
    
    Manager* rManager = new Manager(20, logger);
    SimulationCore* aManager = new SimulationCore(rManager, logger);
    
    Customer* rCustomer = new Customer(stateShop, logger);
    Agent* aCustomer = new Agent(2, aManager, rCustomer);
    aManager->registerAgent(aCustomer);

    Shop* rShop = new Shop(20, stateShop, logger);
    Agent* aShop = new Agent(3, aManager, rShop);
    aManager->registerAgent(aShop);

    Line* rLine = new Line(stateShop, logger);
    Agent* aLine1 = new Agent(4, aManager, rLine);
    Agent* aLine2 = new Agent(5, aManager, rLine);
    aManager->registerAgent(aLine1);
    aManager->registerAgent(aLine2);

    Cash* rCash1 = new Cash({100, 500, 900}, 500, 70, stateShop, logger);
    Cash* rCash2 = new Cash({200, 600, 1000}, 500, 80, stateShop, logger);
    Agent* aCash1 = new Agent(6, aManager, rCash1);
    Agent* aCash2 = new Agent(7, aManager, rCash2);
    aManager->registerAgent(aCash1);
    aManager->registerAgent(aCash2);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
    Graph* rGraph = new Graph(60, window, stateShop, logger);
    Agent* aGraph = new Agent(8, aManager, rGraph);
    aManager->registerAgent(aGraph);

    aManager->runSimulation();
    delete logger;

    return 0;
}
