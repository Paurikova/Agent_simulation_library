#pragma once
//TODO include
#include "library/include/reactiveReasoning.h"

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    float cohere_factor = 0.1;
    float separation = 2.0;
    float separate_factor = 0.25;
    float match_factor = 0.4;
    float visual_distance = 50;
    int number_of_birds = 300;
    std::vector<StateBird*> birds = InitValue;
    sf::RenderWindow& window = InitValue;
    sf::CircleShape shape = InitValue;
    float speed = 3;
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void birdUpdated(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
