#include "../../../../../library/include/simulationCore.h"

#include "../include/Manager1ReactiveReasoning.h"
#include "../include/Customer2ReactiveReasoning.h"
#include "../include/Shop3PetriNetReasoning.h"
#include "../include/Line5PetriNetReasoning.h"
#include "../include/Cash6PetriNetReasoning.h"
#include "../include/state_shop.h"
#include "../include/Graph4ReactiveReasoning.h"
#include "configReader.h"

int main(int argc, char** argv) {
    StateShop* stateShop = new StateShop();
    ConfigReader* configReader = new ConfigReader("/home/miska/CLionProjects/Agent_simulation_library/local.cfg");
    // Create a flock of birds
    Logger* logger = new Logger(false);

    Manager1ReactiveReasoning* rManager = new Manager1ReactiveReasoning(20, logger);
    SimulationCore* aManager = new SimulationCore(rManager, logger);

    Customer2ReactiveReasoning* rCustomer = new Customer2ReactiveReasoning(stateShop, logger);
    Agent* aCustomer = new Agent(2, aManager, rCustomer);
    aManager->registerAgent(aCustomer);

    Shop3PetriNetReasoning* rShop = new Shop3PetriNetReasoning(4, stateShop, logger);
    Agent* aShop = new Agent(3, aManager, rShop);
    aManager->registerAgent(aShop);

    Line5PetriNetReasoning* rLine = new Line5PetriNetReasoning(stateShop, logger);
    Agent* aLine1 = new Agent(4, aManager, rLine);
    Agent* aLine2 = new Agent(5, aManager, rLine);
    aManager->registerAgent(aLine1);
    aManager->registerAgent(aLine2);

    Cash6PetriNetReasoning* rCash1 = new Cash6PetriNetReasoning({100, 500, 900}, 500, 70, stateShop, logger);
    Cash6PetriNetReasoning* rCash2 = new Cash6PetriNetReasoning({200, 600, 1000}, 500, 80, stateShop, logger);
    Agent* aCash1 = new Agent(6, aManager, rCash1);
    Agent* aCash2 = new Agent(7, aManager, rCash2);
    aManager->registerAgent(aCash1);
    aManager->registerAgent(aCash2);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Flocking Simulation");
    Graph4ReactiveReasoning* rGraph = new Graph4ReactiveReasoning(60, window, stateShop, logger);
    Agent* aGraph = new Agent(8, aManager, rGraph);
    aManager->registerAgent(aGraph);

    aManager->runSimulation();
    logger->addToFile();

    delete aManager;
    delete aCustomer;
    delete aShop;
    delete aLine1;
    delete aLine2;
    delete aCash1;
    delete aCash2;
    delete aGraph;

    delete rManager;
    delete rCustomer;
    delete rLine;
    delete rCash1;
    delete rCash2;
    delete rGraph;

    delete logger;
    delete stateShop;
    return 0;
}
