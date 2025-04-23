#include "../../../../library/include/agentManager.h"

#include "../include/manager.h"
#include "../include/customer.h"
#include "../include/shop.h"
#include "../include/line.h"
#include "../include/cash.h"
#include "../include/state_shop.h"
#include "../include/graph.h"

#include "configReader.h"

int main(int argc, char** argv) {
    // Use smart pointers for automatic memory management
    std::unique_ptr<StateShop> stateShop = std::make_unique<StateShop>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);

    std::unique_ptr<SimulationCore> simulationCore = std::make_unique<SimulationCore>(logger.get());

    std::unique_ptr<Manager> rManager = std::make_unique<Manager>(10, logger.get());
    std::unique_ptr<AgentManager> aManager = std::make_unique<AgentManager>(rManager.get(), logger.get());
    simulationCore->registerAgent(aManager.get());
    std::unique_ptr<Customer> rCustomer = std::make_unique<Customer>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCustomer = std::make_unique<Agent>(2, aManager.get(), rCustomer.get());
    simulationCore->registerAgent(aCustomer.get());

    std::unique_ptr<Shop> rShop = std::make_unique<Shop>(2, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aShop = std::make_unique<Agent>(3, aManager.get(), rShop.get());
    simulationCore->registerAgent(aShop.get());

    std::unique_ptr<Line> rLine = std::make_unique<Line>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aLine = std::make_unique<Agent>(4, aManager.get(), rLine.get());
    simulationCore->registerAgent(aLine.get());

    std::unique_ptr<Cash> rCash = std::make_unique<Cash>( 30, 25, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCash = std::make_unique<Agent>(5, aManager.get(), rCash.get());

    simulationCore->registerAgent(aCash.get());

    // Graph agent for visualization
    sf::RenderWindow window(sf::VideoMode(800, 600), "Shop Simulation");
    std::unique_ptr<Graph> rGraph = std::make_unique<Graph>(500, window, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aGraph = std::make_unique<Agent>(6, aManager.get(), rGraph.get());
    simulationCore->registerAgent(aGraph.get());

    // Run the simulation
    simulationCore->runSimulation(1, -1);

    // Write logs to file
    logger->addToFile();

    // No need to manually delete anything, since smart pointers take care of that.
    return 0;
}