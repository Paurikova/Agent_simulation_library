#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>
#include "math.h"

#include "../../../../../library/include/reactiveReasoning.h"
#include "state_bird.h"


class Manager1ReactiveReasoning : public ReactiveReasoning {
private:
    //attributes
    sf::CircleShape shape;
    sf::RenderWindow& window;
    std::vector<StateBird*> birds;
    int number_of_birds = 300;
    float visual_distance = 50;
    float match_factor = 0.4;
    float separate_factor = 0.25;
    float separation = 2.0;
    float cohere_factor = 0.1;
    float speed = 3;
    void normalize_velocity(float& velX, float& velY);
    float distance_to(float x1, float y1, float x2, float y2);
    void calculate_direction(float x1, float y1, float x2, float y2, float &dirX, float &dirY);
    //functions
    void draw(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void birdUpdated(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void move(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void startWindow(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    void inititalization(int pSender, int pReceiver, SimTime_t pExecTime, State* state);
    //registration
    void registerFunctions() override;
public:
    Manager1ReactiveReasoning(float speed, float cohere_factor, float separation, float separate_factor,
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

    ~Manager1ReactiveReasoning();

    void initMessage() override;
};
