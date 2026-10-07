#pragma once

#include "verlet.hpp"
#include <SFML/Graphics.hpp>

class Particle : public VerletObject
{
  public:
    Particle(float radius, sf::Color color, const sf::Vector2f initial_position,
             const sf::Vector2f acceleration)
        : radius_{radius}, color_{color}, VerletObject{initial_position, acceleration} {};

    // Constructor with initial velocity
    Particle(float radius, sf::Color color, const sf::Vector2f initial_position,
             const sf::Vector2f velocity, const sf::Vector2f acceleration, float dt)
        : radius_{radius}, color_{color}, VerletObject{initial_position, acceleration}
    {
        setOldPosition(initial_position - velocity * dt);
    }

    float getRadius() const
    {
        return radius_;
    };
    double getMass() const
    {
        return mass_;
    };
    sf::Color getColor() const
    {
        return color_;
    };

  private:
    float radius_; // radius of the particle
    sf::Color color_;
    float mass_ = std::numbers::pi_v<float> * radius_ * radius_;
};