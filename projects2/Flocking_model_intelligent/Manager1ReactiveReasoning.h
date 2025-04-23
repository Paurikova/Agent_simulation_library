#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    int number_of_birds = 300;
    std::vector<StateBird* birds = InitValue;
    sf::RenderWindow& window = InitValue;
    sf::CircleShape shape = InitValue;
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
