#pragma once
#include "managerAgent.h"

//ID = 1
ManagerAgent::ManagerAgent(int pStartTime, int pEndTime) : Agent(1) {
    currTime = pStartTime;
    endTime = pEndTime;
    registerAgent(this);
    registerFunctions();
}

void ManagerAgent::registerFunctions() {
    registerFunction(1, [this](int sender) {
        allDone(sender);
    });
}

void ManagerAgent::registerAgent(Agent* agent) {
    agents[agent->getId()] = agent;
}

void ManagerAgent::unregisterAgent(int agentId) {
    auto it = agents.find(agentId);
    if (it != agents.end()) {
        agents.erase(it);
    } else {
        throw std::runtime_error("Agent with event ID " + std::to_string(agentId) + " does not exist in the map");
    }
}

void ManagerAgent::runSimulation() {
    //initialization
    initSimulation();
    //run
    while (currTime < endTime) {
        //Agents' initialization
        // Iterate through the map and set the execute attribute of each Agent to true
        for (auto& pair : agents) {
            pair.second->setExecute(true);
        }
        //run tick
        runTick();
        //increase tick
        currTime += SIMULATION_STEP;
    }
}

void ManagerAgent::runTick() {
    int currTick;
    std::cout << "Tick " << currTime << std::endl;
    do {
        currTick = false;
        //run through all agents
        for (auto& pair : agents) {
            //execute is true if it is the first loop or agent has got message
            Agent* agent = pair.second;
            if (agent->getExecute()) {
                //we found agent who has to be executed
                //he can produce another message
                //we have to again control current tick
                currTick = true;
                //execute all messages from agent's schedule
                agent->doTick(currTime);
                //send all messages from agent's message box
                Message msg = agent->getTopMessage();
                while (msg.id != -1) {
                    //find receiver
                    auto it = agents.find(msg.receiver);
                    if (it == agents.end()) {
                        throw std::runtime_error("No agent is registered under ID " + std::to_string(msg.receiver) + ".");
                    }
                    Agent* receiver = agents[msg.receiver];
                    // send msg
                    receiver->receiveMessage(msg);
                    msg = agent->getTopMessage();
                }
            }
        }
    } while (currTick);
}

//functions
void ManagerAgent::allDone(int sender) {
    sendMessage(2,2,currTime+1,3);
    sendMessage(2,3,currTime,3);
}

void ManagerAgent::registerAllFunctions() {
//run through all agents
    for (auto& pair : agents) {
        pair.second->registerFunctions();
    }
}

void ManagerAgent::initSimulation() {
    registerAllFunctions();
}


