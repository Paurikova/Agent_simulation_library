#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "../library/include/reactiveReasoning.h"
#include "state_bird.h"
#include "state_neighbor.h"

class Manager : public ReactiveReasoning {
private:

    int number_of_birds;
    std::vector<StateBird*> birds;
    // Create an SFML window
    sf::RenderWindow& window;



    //function
    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void isWindowOpen(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void handleEvents(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void getPosition(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void clearScreen(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void display(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerFunctions() override;

public:
    Manager(float speed, float cohere_factor, float separation, float separate_factor,
            float match_factor, float visual_distance, int number_of_birds, sf::RenderWindow& window, Logger* logger)
            : ReactiveReasoning(logger), window(window), speed(speed), cohere_factor(cohere_factor), separation(separation),
              separate_factor(separate_factor), match_factor(match_factor),
              visual_distance(visual_distance), number_of_birds(number_of_birds) {
        birds.resize(number_of_birds);
    };
    void initMessage();
};