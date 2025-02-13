#pragma once
//TODO incluce
#include "library/include/reactiveReasoning.h"

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    sf::CircleShape shape = ;
    sf::RenderWindow& window = ;
    std::vector<StateBird*> birds = ;
    int number_of_birds = 300;
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
