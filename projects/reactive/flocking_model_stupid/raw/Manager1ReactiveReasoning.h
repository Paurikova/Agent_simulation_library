#pragma once
//TODO incluce
#include "../../library/include/reactiveReasoning.h"
#include <string>
using namespace std;

class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    sf::CircleShape shape = ;
    sf::RenderWindow& window = ;
    std::vector<StateBird*> birds = ;
    int number_of_birds = 300;
    float visual_distance = 50;
    float match_factor = 0.4;
    float separate_factor = 0.25;
    float separation = 2.0;
    float cohere_factor = 0.1;
    float speed = 3;
    //functions
    void draw(int pSender, SimTime_t pExecTime, State* state);
    void birdUpdated(int pSender, SimTime_t pExecTime, State* state);
    void move(int pSender, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, SimTime_t pExecTime, State* state);
    void inititalization(int pSender, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    void initMessage() override;
};
