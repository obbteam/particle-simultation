#pragma once

#include <SFML/Graphics.hpp>
#include "verlet.hpp"

class Particle : public VerletObject
{
public:
    Particle(float radius, sf::Color color, const sf::Vector2f initial_position, const sf::Vector2f acceleration)
        : _radius{radius}, _color{color}, VerletObject{initial_position, acceleration} {};

    // Constructor with initial velocity
    Particle(float radius, sf::Color color, const sf::Vector2f initial_position, const sf::Vector2f velocity, const sf::Vector2f acceleration, float dt)
        : _radius{radius}, _color{color}, VerletObject{initial_position, acceleration}
    {
        setOldPosition(initial_position - velocity * dt);
    }

    float getRadius() const { return _radius; };
    sf::Color getColor() const { return _color; };

private:
    float _radius; // radius of the particle
    sf::Color _color;
};