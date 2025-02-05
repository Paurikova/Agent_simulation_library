#pragma once
#include <cstdlib> // For rand()
#include <vector>  // For std::vector
#include <SFML/Graphics.hpp>

#include "../library/include/petriNetReasoning.h"

class Manager : public PetriNetReasoning {
private:
    float speed;
    float cohere_factor;
    float separation;
    float separate_factor;
    float match_factor;
    float visual_distance;

    //function
    void Manager::normalize_velocity(float& velX, float& velY) {
    void registerServices() override;

    void registerNodes() override;

public:
    Manager(float speed, float cohere_factor, float separation, float separate_factor,
            float match_factor, float visual_distance)
            : speed(speed), cohere_factor(cohere_factor), separation(separation),
              separate_factor(separate_factor), match_factor(match_factor),
              visual_distance(visual_distance) {};
}