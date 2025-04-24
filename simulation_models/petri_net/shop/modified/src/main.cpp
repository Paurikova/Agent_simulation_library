//TODO include
#include "../include/Customer2ReactiveReasoning.h"
#include "../include/Cash5PetriNetReasoning.h"
#include "../include/Line4ReactiveReasoning.h"
#include "../include/Shop3PetriNetReasoning.h"
#include "../include/Graph6ReactiveReasoning.h"
#include "../include/Manager1ReactiveReasoning.h"
#include "../../../../../library/include/agentManager.h"

int main(int argc, char** argv) {{
    std::unique_ptr<StateShop> stateShop = std::make_unique<StateShop>();
    std::unique_ptr<Logger> logger = std::make_unique<Logger>(false);
    //simulation core
    std::unique_ptr<SimulationCore> simulationCore = std::make_unique<SimulationCore>(logger.get());
    //manager
    std::unique_ptr<Manager1ReactiveReasoning> rManager1ReactiveReasoning = std::make_unique<Manager1ReactiveReasoning>(10, logger.get());
    std::unique_ptr<AgentManager> aManager = std::make_unique<AgentManager>(rManager1ReactiveReasoning.get(), logger.get());
    simulationCore->registerAgent(aManager.get());
    //agents
    std::unique_ptr<Customer2ReactiveReasoning> rCustomer2ReactiveReasoning = std::make_unique<Customer2ReactiveReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCustomer2 = std::make_unique<Agent>(2, aManager.get(), rCustomer2ReactiveReasoning.get());
    simulationCore->registerAgent(aCustomer2.get());
    std::unique_ptr<Cash5PetriNetReasoning> rCash5PetriNetReasoning = std::make_unique<Cash5PetriNetReasoning>(25, 30, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCash5 = std::make_unique<Agent>(5, aManager.get(), rCash5PetriNetReasoning.get());
    simulationCore->registerAgent(aCash5.get());
    std::unique_ptr<Line4ReactiveReasoning> rLine4PetriNetReasoning = std::make_unique<Line4ReactiveReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aLine4 = std::make_unique<Agent>(4, aManager.get(), rLine4PetriNetReasoning.get());
    simulationCore->registerAgent(aLine4.get());
    std::unique_ptr<Shop3PetriNetReasoning> rShop3PetriNetReasoning = std::make_unique<Shop3PetriNetReasoning>(10, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aShop3 = std::make_unique<Agent>(3, aManager.get(), rShop3PetriNetReasoning.get());
    simulationCore->registerAgent(aShop3.get());
        sf::RenderWindow window(sf::VideoMode(800, 600), "Shop Simulation");
    std::unique_ptr<Graph6ReactiveReasoning> rGraph6ReactiveReasoning = std::make_unique<Graph6ReactiveReasoning>(500, window, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aGraph6 = std::make_unique<Agent>(6, aManager.get(), rGraph6ReactiveReasoning.get());
    simulationCore->registerAgent(aGraph6.get());
    simulationCore->runSimulation(1, -1);
    logger->addToFile();
    return 0;
}}