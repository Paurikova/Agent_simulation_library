//TODO include
#include "../include/Customer2ReactiveReasoning.h"
#include "../include/Cash6PetriNetReasoning.h"
#include "../include/Line5ReactiveReasoning.h"
#include "../include/Shop4PetriNetReasoning.h"
#include "../include/Graph3ReactiveReasoning.h"
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
    std::unique_ptr<Cash6PetriNetReasoning> rCash6PetriNetReasoning = std::make_unique<Cash6PetriNetReasoning>(25, 30, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aCash6 = std::make_unique<Agent>(5, aManager.get(), rCash6PetriNetReasoning.get());
    simulationCore->registerAgent(aCash6.get());
    std::unique_ptr<Line5ReactiveReasoning> rLine5PetriNetReasoning = std::make_unique<Line5ReactiveReasoning>(stateShop.get(), logger.get());
    std::unique_ptr<Agent> aLine5 = std::make_unique<Agent>(4, aManager.get(), rLine5PetriNetReasoning.get());
    simulationCore->registerAgent(aLine5.get());
    std::unique_ptr<Shop4PetriNetReasoning> rShop4PetriNetReasoning = std::make_unique<Shop4PetriNetReasoning>(10, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aShop4 = std::make_unique<Agent>(3, aManager.get(), rShop4PetriNetReasoning.get());
    simulationCore->registerAgent(aShop4.get());
        sf::RenderWindow window(sf::VideoMode(800, 600), "Shop Simulation");
    std::unique_ptr<Graph3ReactiveReasoning> rGraph3ReactiveReasoning = std::make_unique<Graph3ReactiveReasoning>(500, window, stateShop.get(), logger.get());
    std::unique_ptr<Agent> aGraph3 = std::make_unique<Agent>(6, aManager.get(), rGraph3ReactiveReasoning.get());
    simulationCore->registerAgent(aGraph3.get());
    simulationCore->runSimulation(1, -1);
    logger->addToFile();
    return 0;
}}