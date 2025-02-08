#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "../library/include/reactiveReasoning.h"
#include "state_bird.h"

class Manager : public ReactiveReasoning {
private:
    float speed;
    float cohere_factor;
    float separation;
    float separate_factor;
    float match_factor;
    float visual_distance;
    int number_of_birds;
    std::vector<StateBird*> birds;
    // Create an SFML window
    sf::RenderWindow& window;
    sf::CircleShape shape;

    void normalize_velocity(float& velX, float& velY);
    float distance_to(float x1, float y1, float x2, float y2);
    void calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY);

    //function
    void initialization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void birdUpdated(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);

    void registerFunctions() override;

public:
    Manager(float speed, float cohere_factor, float separation, float separate_factor,
            float match_factor, float visual_distance, int number_of_birds, sf::RenderWindow& window, Logger* logger)
            : ReactiveReasoning(logger), window(window), speed(speed), cohere_factor(cohere_factor), separation(separation),
              separate_factor(separate_factor), match_factor(match_factor),
              visual_distance(visual_distance), number_of_birds(number_of_birds) {
        // Initialize shape
        shape.setRadius(5);
        shape.setFillColor(sf::Color::White);
        shape.setOrigin(5, 5);  // Center the shape at its origin
        birds.resize(number_of_birds);
    };
    void initMessage();
};