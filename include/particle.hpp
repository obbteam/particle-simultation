#pragma once

#include <SFML/Graphics.hpp>
#include "verlet.hpp"

class Particle : public VerletObject
{
public:
    Particle(float radius, sf::Color color, const sf::Vector2f initial_position, const sf::Vector2f acceleration)
        : radius_{radius}, color_{color}, VerletObject{initial_position, acceleration} {};

    // Constructor with initial velocity
    Particle(float radius, sf::Color color, const sf::Vector2f initial_position, const sf::Vector2f velocity, const sf::Vector2f acceleration, float dt)
        : radius_{radius}, color_{color}, VerletObject{initial_position, acceleration}
    {
        setOldPosition(initial_position - velocity * dt);
    }

    float getRadius() const { return radius_; };
    sf::Color getColor() const { return color_; };

private:
    float radius_; // radius of the particle
    sf::Color color_;
};